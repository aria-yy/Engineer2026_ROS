cmake_minimum_required(VERSION 3.22)
project(mybot_moveit2)

find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)

ament_package()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/launch")
  install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
    PATTERN "setup_assistant.launch" EXCLUDE)
endif()

install(PROGRAMS
    scripts/moveit2_arm_control.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME moveit2_arm_control
)

install(PROGRAMS
    scripts/check_point.py
  DESTINATION lib/${PROJECT_NAME}
  RENAME check_point
)

install(DIRECTORY config DESTINATION share/${PROJECT_NAME})
install(DIRECTORY scripts DESTINATION share/${PROJECT_NAME})
install(FILES .setup_assistant DESTINATION share/${PROJECT_NAME})
