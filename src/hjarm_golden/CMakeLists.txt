cmake_minimum_required(VERSION 3.5)
project(hjarm_golden)

# 查找构建所需的功能包
find_package(ament_cmake REQUIRED)

# 安装资源目录到 share 中
install(DIRECTORY
    meshes/
  DESTINATION share/${PROJECT_NAME}/meshes
)

install(DIRECTORY
    urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)

# 必须保留，用于启用 ament 构建系统
ament_package()
