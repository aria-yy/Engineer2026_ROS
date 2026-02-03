cmake_minimum_required(VERSION 3.8)
project(arm_driver)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)  # 动作通信依赖
find_package(rclpy REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)  # MoveGroupInterface依赖
find_package(control_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)  # JointState消息依赖
find_package(trajectory_msgs REQUIRED)
find_package(ament_cmake_auto REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(actionlib_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/launch")
  install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
    PATTERN "setup_assistant.launch" EXCLUDE)
endif()

# 查找libserial头文件
find_path(LIBSERIAL_INCLUDE_DIRS
  NAMES SerialPort.h SerialStream.h
  PATHS /usr/include /usr/local/include
)

# 查找libserial库文件
find_library(LIBSERIAL_LIBRARIES
  NAMES serial
  PATHS /usr/lib /usr/local/lib
)

include_directories(
  include
)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/JointCommand.msg"   
  DEPENDENCIES std_msgs
)

add_executable(hjarm_engineer_node
  src/hjarm_engineer.cpp
)
ament_target_dependencies(hjarm_engineer_node
  rclcpp
  rclcpp_action
  control_msgs
  std_msgs
  sensor_msgs
  trajectory_msgs
  actionlib_msgs
)

rosidl_target_interfaces(hjarm_engineer_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

target_link_libraries(hjarm_engineer_node ${LIBSERIAL_LIBRARIES})

install(TARGETS
  hjarm_engineer_node
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
    scripts/moveit2_arm_control.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME moveit2_arm_control
)

install(PROGRAMS
    scripts/keyboard_servo.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME keyboard_servo
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()