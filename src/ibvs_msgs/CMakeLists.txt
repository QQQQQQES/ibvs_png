cmake_minimum_required(VERSION 3.0.2)
project(ibvs_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
  geometry_msgs
  sensor_msgs
)

add_message_files(
  FILES
  TargetState.msg
  ImageFeatures.msg
  ControlCommand.msg
  TrajectoryPoint.msg
)

add_service_files(
  FILES
  SetTarget.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime std_msgs geometry_msgs sensor_msgs
)
