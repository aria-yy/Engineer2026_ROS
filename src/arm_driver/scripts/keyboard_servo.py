#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
from std_msgs.msg import Bool
import sys, select, termios, tty

key_bindings = {
    'w': (0.05, 0.0, 0.0, 0.0, 0.0, 0.0),
    's': (-0.05, 0.0, 0.0, 0.0, 0.0, 0.0),
    'a': (0.0, 0.05, 0.0, 0.0, 0.0, 0.0),
    'd': (0.0, -0.05, 0.0, 0.0, 0.0, 0.0),
    'q': (0.0, 0.0, 0.05, 0.0, 0.0, 0.0),
    'e': (0.0, 0.0, -0.05, 0.0, 0.0, 0.0),
    'j': (0.0, 0.0, 0.0, 0.0, 0.0, 0.2),
    'l': (0.0, 0.0, 0.0, 0.0, 0.0, -0.2),
    'i': (0.0, 0.0, 0.0, 0.2, 0.0, 0.0),
    'k': (0.0, 0.0, 0.0, -0.2, 0.0, 0.0),
    'u': (0.0, 0.0, 0.0, 0.0, 0.2, 0.0),
    'o': (0.0, 0.0, 0.0, 0.0, -0.2, 0.0),
}

class KeyboardServo(Node):
    def __init__(self):
        super().__init__('keyboard_servo')
        self.publisher_ = self.create_publisher(TwistStamped, '/servo_node/delta_twist_cmds', 10)
        self.enable_pub = self.create_publisher(Bool, '/servo_node/enable', 10)
        timer_period = 0.1  # 10 Hz
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.current_twist = [0.0] * 6  # x, y, z, roll, pitch, yaw
        self.enabled = True
        # 发布一次启用信号
        enable_msg = Bool()
        enable_msg.data = True
        self.enable_pub.publish(enable_msg)

    def update_twist(self, key):
        if key in key_bindings:
            self.current_twist = list(key_bindings[key])
            print("按下" + key)
        else:
            self.current_twist = [0.0] * 6

    def timer_callback(self):
        msg = TwistStamped()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "base_link"
        msg.twist.linear.x = float(self.current_twist[0])
        msg.twist.linear.y = float(self.current_twist[1])
        msg.twist.linear.z = (self.current_twist[2])
        msg.twist.angular.x = float(self.current_twist[3])
        msg.twist.angular.y = float(self.current_twist[4])
        msg.twist.angular.z = float(self.current_twist[5])
        self.publisher_.publish(msg)

def getKey(settings):
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def main(args=None):
    rclpy.init(args=args)
    node = KeyboardServo()
    settings = termios.tcgetattr(sys.stdin)

    print("=== Keyboard Servo Control ===")
    print("WASDQE: 移动 XYZ")
    print("UIOJKL: 旋转 RPY")
    print("空格: 停止")
    print("z: 退出")

    try:
        while rclpy.ok():
            key = getKey(settings)
            if key == 'z': 
                print("breakk")
                break
            elif key == ' ':  # 空格：停止
                print("停止")
                node.update_twist(' ')
            else:
                node.update_twist(key)
            rclpy.spin_once(node, timeout_sec=0.01)
    except Exception as e:
        print(e)
    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        # 发送零速度停止
        node.current_twist = [0.0] * 6
        for _ in range(5):
            node.timer_callback()
            rclpy.spin_once(node, timeout_sec=0.01)
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()