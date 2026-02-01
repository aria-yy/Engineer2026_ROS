#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from arm_driver.msg import CustomData
from geometry_msgs.msg import TwistStamped
import struct
import serial
import math

def uint_to_float(x_int, x_min, x_max, bits):
    # 无符号整数转浮点数（给定范围和位数）
    span = x_max - x_min
    offset = x_min
    return float(x_int) * span / float((1 << bits) - 1) + offset

def float_to_uint(x, x_min, x_max, bits):
    # 浮点数转无符号整数（给定范围和位数）
    span = x_max - x_min
    offset = x_min
    return int((x - offset) * float((1 << bits) - 1) / span)

def consider_as_zero(value, threshold=0.001):
    # 小于阈值的值视为0
    if abs(value) < threshold:
        return 0.0
    else:
        return value

class SerialReceiverNode(Node):
    def __init__(self, serial_port, baudrate=115200):
        super().__init__('serial_receiver_node')
        
        # 打开串口
        try:
            self.ser = serial.Serial(serial_port, baudrate, timeout=1)
            self.get_logger().info(f"成功打开串口: {serial_port}")
        except serial.SerialException as e:
            self.get_logger().error(f"无法打开串口 {serial_port}: {e}")
            raise
        
        # 创建发布者
        self.pub_custom = self.create_publisher(
            CustomData, 
            '/hjarm_engineer_driver/custom_data', 
            10
        )
        self.pub_twist = self.create_publisher(
            TwistStamped, 
            '/servo_server/delta_twist_cmds', 
            10
        )
        
        # 初始化消息对象
        self.custom_data = CustomData()
        self.twist_msg = TwistStamped()
        
        # 创建定时器循环读取串口数据（100Hz）
        self.timer = self.create_timer(0.01, self.read_and_publish)

    def read_and_publish(self):
        # 读取18字节串口数据
        serial_buffer = self.ser.read(18)
        
        # 解析数据并发布
        success = self.decode_data(serial_buffer)
        if success:
            self.twist_msg.header.stamp = self.get_clock().now().to_msg()
            self.pub_custom.publish(self.custom_data)
            self.pub_twist.publish(self.twist_msg)

    def decode_data(self, buffer):
        # 检查数据有效性
        if buffer is None or len(buffer) < 18:
            return False
        
        # 解析二进制数据
        try:
            (self.custom_data.frame_header, self.custom_data.index,
             self.custom_data.yaw_v_LSB, self.custom_data.yaw_v_MSB,
             self.custom_data.pitch_v_LSB, self.custom_data.pitch_v_MSB,
             self.custom_data.roll_v_LSB, self.custom_data.roll_v_MSB,
             self.custom_data.x_v_LSB, self.custom_data.x_v_MSB,
             self.custom_data.y_v_LSB, self.custom_data.y_v_MSB,
             self.custom_data.z_v_LSB, self.custom_data.z_v_MSB,
             self.custom_data.sucker, self.custom_data.reset,
             self.custom_data.rsvd_1, self.custom_data.csum) = struct.unpack('18B', buffer[0:18])
        except struct.error as e:
            self.get_logger().warn(f"数据解析失败: {e}")
            return False
        
        # 校验和验证
        checksum = (self.custom_data.index 
                  + self.custom_data.yaw_v_LSB 
                  + self.custom_data.yaw_v_MSB 
                  + self.custom_data.pitch_v_LSB 
                  + self.custom_data.pitch_v_MSB 
                  + self.custom_data.roll_v_LSB 
                  + self.custom_data.roll_v_MSB 
                  + self.custom_data.x_v_LSB 
                  + self.custom_data.x_v_MSB 
                  + self.custom_data.y_v_LSB 
                  + self.custom_data.y_v_MSB 
                  + self.custom_data.z_v_LSB 
                  + self.custom_data.z_v_MSB 
                  + self.custom_data.sucker 
                  + self.custom_data.reset 
                  + self.custom_data.rsvd_1) % 256
        
        if checksum != self.custom_data.csum:
            self.get_logger().warn(f"校验和错误: 计算值={checksum}, 接收值={self.custom_data.csum}")
            return False
        
        # 解析速度数据
        self.twist_msg.twist.linear.y = uint_to_float(
            self.custom_data.x_v_MSB << 8 | self.custom_data.x_v_LSB, -10, 10, 16)
        self.twist_msg.twist.linear.x = -uint_to_float(
            self.custom_data.y_v_MSB << 8 | self.custom_data.y_v_LSB, -10, 10, 16)
        self.twist_msg.twist.linear.z = uint_to_float(
            self.custom_data.z_v_MSB << 8 | self.custom_data.z_v_LSB, -10, 10, 16)
        self.twist_msg.twist.angular.y = -uint_to_float(
            self.custom_data.roll_v_MSB << 8 | self.custom_data.roll_v_LSB, -10, 10, 16)
        self.twist_msg.twist.angular.x = uint_to_float(
            self.custom_data.pitch_v_MSB << 8 | self.custom_data.pitch_v_LSB, -10, 10, 16)
        self.twist_msg.twist.angular.z = uint_to_float(
            self.custom_data.yaw_v_MSB << 8 | self.custom_data.yaw_v_LSB, -10, 10, 16)
        
        # 处理小值和缩放
        self.twist_msg.twist.linear.x = consider_as_zero(self.twist_msg.twist.linear.x)
        self.twist_msg.twist.linear.y = consider_as_zero(self.twist_msg.twist.linear.y)
        self.twist_msg.twist.linear.z = consider_as_zero(self.twist_msg.twist.linear.z)
        self.twist_msg.twist.angular.x = consider_as_zero(self.twist_msg.twist.angular.x)
        self.twist_msg.twist.angular.y = consider_as_zero(self.twist_msg.twist.angular.y)
        self.twist_msg.twist.angular.z = consider_as_zero(self.twist_msg.twist.angular.z)
        
        # 缩放处理
        self.twist_msg.twist.linear.x = math.floor(self.twist_msg.twist.linear.x * 100) / 100 * 10
        self.twist_msg.twist.linear.y = math.floor(self.twist_msg.twist.linear.y * 100) / 100 * 10
        self.twist_msg.twist.linear.z = math.floor(self.twist_msg.twist.linear.z * 100) / 100 * 3
        self.twist_msg.twist.angular.x = math.floor(self.twist_msg.twist.angular.x * 100) / 100 * 12
        self.twist_msg.twist.angular.y = math.floor(self.twist_msg.twist.angular.y * 100) / 100 * 12
        self.twist_msg.twist.angular.z = math.floor(self.twist_msg.twist.angular.z * 100) / 100 * 12
        
        # 日志输出
        self.get_logger().info(
            f"接收数据: frame_header={self.custom_data.frame_header}, index={self.custom_data.index}, "
            f"yaw_v=%.2f, pitch_v=%.2f, roll_v=%.2f, x_v=%.2f, y_v=%.2f, z_v=%.2f, "
            f"sucker={self.custom_data.sucker}, reset={self.custom_data.reset}, "
            f"Rsvd_1={self.custom_data.rsvd_1}, Csum={self.custom_data.csum}" %
            (self.twist_msg.twist.angular.z, self.twist_msg.twist.angular.y,
             self.twist_msg.twist.angular.x, self.twist_msg.twist.linear.x,
             self.twist_msg.twist.linear.y, self.twist_msg.twist.linear.z)
        )
        
        return True

    def destroy_node(self):
        # 关闭串口
        if hasattr(self, 'ser') and self.ser.is_open:
            self.ser.close()
            self.get_logger().info("串口已关闭")
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    
    # 串口配置（根据实际情况修改）
    serial_port = '/dev/ttyUSB0'
    
    try:
        node = SerialReceiverNode(serial_port)
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("程序被用户终止")
    finally:
        if rclpy.ok():
            node.destroy_node()
            rclpy.shutdown()

if __name__ == '__main__':
    main()