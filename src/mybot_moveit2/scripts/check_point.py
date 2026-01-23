#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
import math

# MoveIt 2 消息接口
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import Constraints, PositionConstraint, OrientationConstraint, BoundingVolume
from geometry_msgs.msg import Point, Quaternion, Pose, PoseStamped
from shape_msgs.msg import SolidPrimitive
from moveit_msgs.msg import MoveItErrorCodes

class MoveIt2Planner(Node):
    def __init__(self):
        super().__init__('moveit2_single_planner')
        
        # 创建动作客户端
        self.move_group_client = ActionClient(self, MoveGroup, 'move_action')
        
        # 等待服务器就绪
        while not self.move_group_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().info('等待 move_group 服务器...')
        
        self.get_logger().info("MoveIt 2 规划器初始化完成")
        self.ee_link = "Link6" 
        self.plan_complete = False 

    def normalize_quaternion(self, quat):
        """归一化四元数"""
        x, y, z, w = quat
        norm = math.sqrt(x**2 + y**2 + z**2 + w**2)
        return [x/norm, y/norm, z/norm, w/norm] if norm > 1e-6 else [0.0, 0.0, 0.0, 1.0]

    def plan_to_position(self, planning_group, position):
        """规划到目标位置（只控制位置，姿态由MoveIt自动计算）"""
        # 验证输入
        if len(position) != 3:
            self.get_logger().error("位置参数错误")
            self.plan_complete = True
            return

        # 创建规划目标
        goal_msg = MoveGroup.Goal()
        goal_msg.request.group_name = planning_group
        goal_msg.request.num_planning_attempts = 10 
        goal_msg.request.allowed_planning_time = 15.0  
        goal_msg.request.planner_id = "RRTConnect"
        
        # 设置位置约束（相对于基座坐标系）
        constraints = Constraints()
        
        # 位置约束
        pos_constraint = PositionConstraint()
        pos_constraint.header.frame_id = "base_link"  # 相对于基座坐标系
        pos_constraint.link_name = self.ee_link
        
        # 创建边界体积（使用很小的容差来精确定位）
        bounding_volume = BoundingVolume()
        sphere = SolidPrimitive(type=SolidPrimitive.SPHERE, dimensions=[0.005])  # 5mm容差
        sphere_pose = Pose()
        sphere_pose.position = Point(x=position[0], y=position[1], z=position[2])
        bounding_volume.primitives.append(sphere)
        bounding_volume.primitive_poses.append(sphere_pose)
        
        pos_constraint.constraint_region = bounding_volume
        pos_constraint.weight = 1.0
        
        constraints.position_constraints.append(pos_constraint)
        
        # 不设置姿态约束，让MoveIt自动计算合适的姿态
        goal_msg.request.goal_constraints.append(constraints)
        
        goal_msg.planning_options.plan_only = False  # False表示规划后执行
        goal_msg.planning_options.look_around = False
        goal_msg.planning_options.look_around_attempts = 0
        goal_msg.planning_options.replan = True
        goal_msg.planning_options.replan_attempts = 3
        goal_msg.planning_options.replan_delay = 2.0
        
        self.get_logger().info(f"发送规划目标到 '{planning_group}'...")
        self.get_logger().info(f"目标位置 (相对于base_link): [{position[0]:.3f}, {position[1]:.3f}, {position[2]:.3f}]")
        
        # 发送规划请求并注册回调
        future = self.move_group_client.send_goal_async(goal_msg)
        future.add_done_callback(self.goal_response_callback)

    def plan_to_pose_with_fixed_orientation(self, planning_group, position, fixed_orientation=None):
        """规划到目标位置，使用固定姿态（可选）"""
        if len(position) != 3:
            self.get_logger().error("位置参数错误")
            self.plan_complete = True
            return

        # 默认姿态：末端执行器朝下（适合吸取操作）
        if fixed_orientation is None:
            fixed_orientation = [0.0, 1.0, 0.0, 0.0]  # 绕Y轴旋转180度，末端朝下
        
        norm_quat = self.normalize_quaternion(fixed_orientation)

        goal_msg = MoveGroup.Goal()
        goal_msg.request.group_name = planning_group
        goal_msg.request.num_planning_attempts = 10
        goal_msg.request.allowed_planning_time = 15.0
        goal_msg.request.planner_id = "RRTConnect"
        
        constraints = Constraints()
        
        # 位置约束
        pos_constraint = PositionConstraint()
        pos_constraint.header.frame_id = "base_link"
        pos_constraint.link_name = self.ee_link
        
        bounding_volume = BoundingVolume()
        sphere = SolidPrimitive(type=SolidPrimitive.SPHERE, dimensions=[0.005])  # 5mm容差
        sphere_pose = Pose()
        sphere_pose.position = Point(x=position[0], y=position[1], z=position[2])
        bounding_volume.primitives.append(sphere)
        bounding_volume.primitive_poses.append(sphere_pose)
        
        pos_constraint.constraint_region = bounding_volume
        pos_constraint.weight = 1.0
        
        # 姿态约束（固定姿态）
        orient_constraint = OrientationConstraint()
        orient_constraint.header.frame_id = "base_link"
        orient_constraint.link_name = self.ee_link
        orient_constraint.orientation = Quaternion(
            x=norm_quat[0], y=norm_quat[1], z=norm_quat[2], w=norm_quat[3]
        )
        orient_constraint.absolute_x_axis_tolerance = 0.2  # 放宽姿态容差
        orient_constraint.absolute_y_axis_tolerance = 0.2
        orient_constraint.absolute_z_axis_tolerance = 0.2
        orient_constraint.weight = 1.0
        
        constraints.position_constraints.append(pos_constraint)
        constraints.orientation_constraints.append(orient_constraint)
        goal_msg.request.goal_constraints.append(constraints)
        
        goal_msg.planning_options.plan_only = False
        goal_msg.planning_options.look_around = False
        goal_msg.planning_options.replan = True
        goal_msg.planning_options.replan_attempts = 3
        
        self.get_logger().info(f"发送规划目标到 '{planning_group}'...")
        self.get_logger().info(f"目标位置: [{position[0]:.3f}, {position[1]:.3f}, {position[2]:.3f}]")
        self.get_logger().info(f"固定姿态: [{norm_quat[0]:.3f}, {norm_quat[1]:.3f}, {norm_quat[2]:.3f}, {norm_quat[3]:.3f}]")
        
        future = self.move_group_client.send_goal_async(goal_msg)
        future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        """处理目标是否被接受"""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error("规划目标被服务器拒绝")
            self.plan_complete = True
            return
        
        self.get_logger().info("目标已接受，正在规划并执行路径...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.plan_result_callback)

    def plan_result_callback(self, future):
        """处理规划执行结果"""
        try:
            result = future.result().result
            error_code = result.error_code.val
            
            if error_code == MoveItErrorCodes.SUCCESS:
                self.get_logger().info("路径规划并执行成功")
            elif error_code == MoveItErrorCodes.NO_IK_SOLUTION:
                self.get_logger().error("无逆运动学解，目标位置不可达")
            elif error_code == MoveItErrorCodes.TIMED_OUT:
                self.get_logger().error("规划超时")
            elif error_code == MoveItErrorCodes.INVALID_GOAL_CONSTRAINTS:
                self.get_logger().error("无效的目标约束")
            elif error_code == MoveItErrorCodes.INVALID_LINK_NAME:
                self.get_logger().error(f"无效的链接名称: {self.ee_link}")
            else:
                self.get_logger().error(f"规划执行失败，错误码: {error_code}")
                
        except Exception as e:
            self.get_logger().error(f"处理结果出错: {str(e)}")
        
        finally:
            self.plan_complete = True

def main(args=None):
    rclpy.init(args=args)
    
    try:
        planner = MoveIt2Planner()

        # 测试位置（相对于机械臂基座几何中心）
        target_position = [-0.145, 0.417, 0.544]  # XYZ坐标
        
        # 方法1：只控制位置，姿态自动计算（推荐）
        planner.get_logger().info("=== 方法1: 只控制位置，姿态自动计算 ===")
        planner.plan_to_position("test_group", target_position)
        
        # 运行直到规划/执行完成
        while rclpy.ok() and not planner.plan_complete:
            rclpy.spin_once(planner, timeout_sec=0.1)
        
        # 重置完成标志，准备下一次规划
        planner.plan_complete = False
        
        # #可选：方法2：控制位置和固定姿态
        # planner.get_logger().info("=== 方法2: 控制位置和固定姿态 ===")
        # fixed_orientation = [0.0, 1.0, 0.0, 0.0]  # 末端朝下
        # planner.plan_to_pose_with_fixed_orientation("test_group", target_position, fixed_orientation)
        
        while rclpy.ok() and not planner.plan_complete:
            rclpy.spin_once(planner, timeout_sec=0.1)
        
        planner.get_logger().info("规划执行流程结束")
        
    except KeyboardInterrupt:
        planner.get_logger().info("用户中断")
    except Exception as e:
        planner.get_logger().error(f"程序异常: {str(e)}")
    finally:
        planner.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()