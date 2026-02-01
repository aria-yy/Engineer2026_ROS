from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, ExecuteProcess,TimerAction
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
from launch.actions import (
    IncludeLaunchDescription,
    RegisterEventHandler,
    LogInfo
)
from launch.event_handlers import OnProcessStart

def generate_launch_description():
    
    
    moveit_start_node=IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                FindPackageShare('mybot_moveit2'),'/launch','/demo.launch.py'
            ])
        )

    bridge_node=Node(
            package='arm_driver',
            executable='hjarm_engineer_node',
            name='controller',
            output='screen',
            arguments=['--log-level', 'debug'], 
        )
    
    point_node=Node(
            package='arm_driver',
            executable='moveit2_arm_control',
            name='controller',
            output='screen',
        )
    
    return LaunchDescription([
      
        bridge_node,

        TimerAction(
            period=5.0,
            actions=[moveit_start_node]
        ),

        RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action=bridge_node, 
            on_start=[
                point_node 
            ]
        )
    )

    ])