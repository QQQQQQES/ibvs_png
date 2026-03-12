cmake_minimum_required(VERSION 3.0.2)
project(target_detection)

add_compile_options(-std=c++14)

# Debug mode: add debug symbols and disable optimization
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  geometry_msgs
  cv_bridge
  image_transport
  ibvs_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES target_detection
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs geometry_msgs cv_bridge image_transport ibvs_msgs tf2 tf2_ros
  DEPENDS OpenCV EIGEN3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

# Target detector library
add_library(target_detection
  src/target_detector.cpp
  src/feature_tracker.cpp
  src/depth_estimator.cpp
  src/kalman_filter.cpp
)

target_link_libraries(target_detection
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

# Target detection node
add_executable(target_detection_node
  src/target_detection_node.cpp
)

target_link_libraries(target_detection_node
  target_detection
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

install(TARGETS target_detection target_detection_node
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
