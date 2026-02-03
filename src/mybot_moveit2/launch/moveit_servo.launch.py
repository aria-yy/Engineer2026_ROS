# launch/servo.launch.py
import os
import yaml
from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder
from ament_index_python.packages import get_package_share_directory

def load_yaml(pkg, path):
    return yaml.safe_load(open(os.path.join(get_package_share_directory(pkg), path)))

def generate_launch_description():
    moveit_config = MoveItConfigsBuilder("hjarm_golden", package_name="mybot_moveit2") \
        .robot_description(file_path="config/hjarm_golden.urdf.xacro") \
        .robot_description_semantic(file_path="config/hjarm_golden.srdf") \
        .robot_description_kinematics(file_path="config/kinematics.yaml") \
        .planning_pipelines() \
        .to_moveit_configs()

    servo_config = load_yaml("mybot_moveit2", "config/servo.yaml")

    servo_params = {
        "enable": True,
        "moveit_servo": servo_config,  
    }
    servo_params.update(moveit_config.robot_description)
    servo_params.update(moveit_config.robot_description_semantic)
    servo_params.update(moveit_config.robot_description_kinematics)

    return LaunchDescription([
        Node(
            package="moveit_servo",
            executable="servo_node_main",
            name="servo_node",
            parameters=[servo_params],
            output="screen"
        )
    ])