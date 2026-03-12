# Install script for directory: /home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/zml/桌面/ibvs_png_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/msg" TYPE FILE FILES
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/AuxCommand.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Corrections.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Gains.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/GoalSet.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/OutputData.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/PositionCommand.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/PPROutputData.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Serial.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/SO3Command.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/StatusData.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/TRPYCommand.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Odometry.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/PolynomialTrajectory.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/OptimalTimeAllocator.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/TrajectoryMatrix.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/ReplanCheck.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/SpatialTemporalTrajectory.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Bspline.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/SwarmCommand.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Replan.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/SwarmOdometry.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/SwarmInfo.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/Px4ctrlDebug.msg"
    "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/msg/TakeoffLand.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES "/home/zml/桌面/ibvs_png_ws/build/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/zml/桌面/ibvs_png_ws/devel/include/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/zml/桌面/ibvs_png_ws/devel/share/roseus/ros/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/zml/桌面/ibvs_png_ws/devel/share/common-lisp/ros/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/zml/桌面/ibvs_png_ws/devel/share/gennodejs/ros/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/zml/桌面/ibvs_png_ws/devel/lib/python3/dist-packages/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/zml/桌面/ibvs_png_ws/devel/lib/python3/dist-packages/quadrotor_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zml/桌面/ibvs_png_ws/build/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES "/home/zml/桌面/ibvs_png_ws/build/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES
    "/home/zml/桌面/ibvs_png_ws/build/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgsConfig.cmake"
    "/home/zml/桌面/ibvs_png_ws/build/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs" TYPE FILE FILES "/home/zml/桌面/ibvs_png_ws/src/quadrotor_msgs/package.xml")
endif()

