cmake_minimum_required(VERSION 3.0.2)
project(visual_servo_controller)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  nav_msgs
  ibvs_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
)

find_package(Eigen3 REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES visual_servo_controller
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs nav_msgs ibvs_msgs tf2 tf2_ros
  DEPENDS EIGEN3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

# IBVS controller library
add_library(visual_servo_controller
  src/ibvs_controller.cpp
)

target_link_libraries(visual_servo_controller
  ${catkin_LIBRARIES}
)

# Visual servo controller node
add_executable(visual_servo_controller_node
  src/visual_servo_controller_node.cpp
)

target_link_libraries(visual_servo_controller_node
  visual_servo_controller
  ${catkin_LIBRARIES}
)

install(TARGETS visual_servo_controller visual_servo_controller_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
