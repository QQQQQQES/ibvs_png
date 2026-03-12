# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ibvs_msgs: 4 messages, 1 services")

set(MSG_I_FLAGS "-Iibvs_msgs:/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ibvs_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_custom_target(_ibvs_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ibvs_msgs" "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" "geometry_msgs/Vector3:geometry_msgs/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_custom_target(_ibvs_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ibvs_msgs" "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" "geometry_msgs/Vector3:geometry_msgs/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_custom_target(_ibvs_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ibvs_msgs" "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_custom_target(_ibvs_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ibvs_msgs" "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" "geometry_msgs/Vector3:geometry_msgs/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_custom_target(_ibvs_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ibvs_msgs" "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_cpp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_cpp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_cpp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
)

### Generating Services
_generate_srv_cpp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
)

### Generating Module File
_generate_module_cpp(ibvs_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ibvs_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ibvs_msgs_generate_messages ibvs_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_cpp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_cpp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_cpp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_cpp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_cpp _ibvs_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ibvs_msgs_gencpp)
add_dependencies(ibvs_msgs_gencpp ibvs_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ibvs_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_eus(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_eus(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_eus(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
)

### Generating Services
_generate_srv_eus(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
)

### Generating Module File
_generate_module_eus(ibvs_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ibvs_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ibvs_msgs_generate_messages ibvs_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_eus _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_eus _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_eus _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_eus _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_eus _ibvs_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ibvs_msgs_geneus)
add_dependencies(ibvs_msgs_geneus ibvs_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ibvs_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_lisp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_lisp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_lisp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
)

### Generating Services
_generate_srv_lisp(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
)

### Generating Module File
_generate_module_lisp(ibvs_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ibvs_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ibvs_msgs_generate_messages ibvs_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_lisp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_lisp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_lisp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_lisp _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_lisp _ibvs_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ibvs_msgs_genlisp)
add_dependencies(ibvs_msgs_genlisp ibvs_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ibvs_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_nodejs(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_nodejs(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_nodejs(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
)

### Generating Services
_generate_srv_nodejs(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
)

### Generating Module File
_generate_module_nodejs(ibvs_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(ibvs_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(ibvs_msgs_generate_messages ibvs_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_nodejs _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_nodejs _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_nodejs _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_nodejs _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_nodejs _ibvs_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ibvs_msgs_gennodejs)
add_dependencies(ibvs_msgs_gennodejs ibvs_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ibvs_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_py(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_py(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
)
_generate_msg_py(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
)

### Generating Services
_generate_srv_py(ibvs_msgs
  "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
)

### Generating Module File
_generate_module_py(ibvs_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ibvs_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ibvs_msgs_generate_messages ibvs_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TargetState.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_py _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ImageFeatures.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_py _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/ControlCommand.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_py _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/msg/TrajectoryPoint.msg" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_py _ibvs_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zml/桌面/ibvs_png_ws/src/ibvs_msgs/srv/SetTarget.srv" NAME_WE)
add_dependencies(ibvs_msgs_generate_messages_py _ibvs_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ibvs_msgs_genpy)
add_dependencies(ibvs_msgs_genpy ibvs_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ibvs_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ibvs_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(ibvs_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(ibvs_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(ibvs_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ibvs_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(ibvs_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(ibvs_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(ibvs_msgs_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ibvs_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(ibvs_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(ibvs_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(ibvs_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ibvs_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(ibvs_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(ibvs_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(ibvs_msgs_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ibvs_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(ibvs_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(ibvs_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(ibvs_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
