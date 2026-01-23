import os
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch import LaunchDescription
from launch.actions import ExecuteProcess, DeclareLaunchArgument
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from moveit_configs_utils import MoveItConfigsBuilder
from ament_index_python.packages import get_package_share_directory
import subprocess

def generate_launch_description():  
    pkg_description = get_package_share_directory('hjarm_golden')

    moveit_config = (
        MoveItConfigsBuilder("hjarm_golden", package_name="mybot_moveit2")
        .to_moveit_configs()
    )

    ros2_controllers_path = PathJoinSubstitution(
        [
            FindPackageShare("mybot_moveit2"), 
            "config",
            "ros2_controllers.yaml",]
    )
    
    initial_positions_file = os.path.join(get_package_share_directory('mybot_moveit2'),'config' , 'initial_positions.yaml')

    xacro_file = os.path.join(get_package_share_directory('mybot_moveit2'),'config' , 'hjarm_golden.urdf.xacro')

    result = subprocess.run(
        ['xacro' , xacro_file,
         f'initial_positions_file:={initial_positions_file}',
         'use_sim:=true'],
         capture_output=True,
         text=True,
         check=True
    )
    robot_description_content = result.stdout

    robot_description_content = robot_description_content.replace(
        '<plugin name="gazebo_ros2_control" filename="libgazebo_ros2_control.so">\n        </plugin>',
        f'<plugin name="gazebo_ros2_control" filename="libgazebo_ros2_control.so">\n                <parameters>{ros2_controllers_path}</parameters>\n        </plugin>'
    )

    robot_description_content = robot_description_content.replace(
        'package://hjarm_golden',
        f'file://{pkg_description}',
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="screen",
        parameters=[{
            'robot_description':robot_description_content,
            'use_sim_time': True
        }],  
    )       

    start_gazebo_server = ExecuteProcess(
        cmd=['gzserver', '--verbose' , '-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so'],
        output='screen'
    )
    start_gazebo_client = ExecuteProcess(cmd=['gzclient'], output='screen')

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description', '-entity', 'hjarm_golden'],
        output='screen'
    )

    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[""]
    )
    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='true', description='Use simulation (Gazebo) clock'),
        start_gazebo_server,
        start_gazebo_client,
        robot_state_publisher,
        spawn_entity,
    ])