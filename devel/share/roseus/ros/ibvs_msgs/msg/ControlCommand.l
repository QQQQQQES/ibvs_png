;; Auto-generated. Do not edit!


(when (boundp 'ibvs_msgs::ControlCommand)
  (if (not (find-package "IBVS_MSGS"))
    (make-package "IBVS_MSGS"))
  (shadow 'ControlCommand (find-package "IBVS_MSGS")))
(unless (find-package "IBVS_MSGS::CONTROLCOMMAND")
  (make-package "IBVS_MSGS::CONTROLCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude ControlCommand.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*IBVS_MODE*" (find-package "IBVS_MSGS::CONTROLCOMMAND"))
(shadow '*IBVS_MODE* (find-package "IBVS_MSGS::CONTROLCOMMAND"))
(defconstant ibvs_msgs::ControlCommand::*IBVS_MODE* 0)
(intern "*TRAJECTORY_MODE*" (find-package "IBVS_MSGS::CONTROLCOMMAND"))
(shadow '*TRAJECTORY_MODE* (find-package "IBVS_MSGS::CONTROLCOMMAND"))
(defconstant ibvs_msgs::ControlCommand::*TRAJECTORY_MODE* 1)

(defun ibvs_msgs::ControlCommand-to-symbol (const)
  (cond
        ((= const 0) 'ibvs_msgs::ControlCommand::*IBVS_MODE*)
        ((= const 1) 'ibvs_msgs::ControlCommand::*TRAJECTORY_MODE*)
        (t nil)))

(defclass ibvs_msgs::ControlCommand
  :super ros::object
  :slots (_header _linear_velocity _angular_velocity _mode ))

(defmethod ibvs_msgs::ControlCommand
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:linear_velocity __linear_velocity) (instance geometry_msgs::Vector3 :init))
    ((:angular_velocity __angular_velocity) (instance geometry_msgs::Vector3 :init))
    ((:mode __mode) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _linear_velocity __linear_velocity)
   (setq _angular_velocity __angular_velocity)
   (setq _mode (round __mode))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:linear_velocity
   (&rest __linear_velocity)
   (if (keywordp (car __linear_velocity))
       (send* _linear_velocity __linear_velocity)
     (progn
       (if __linear_velocity (setq _linear_velocity (car __linear_velocity)))
       _linear_velocity)))
  (:angular_velocity
   (&rest __angular_velocity)
   (if (keywordp (car __angular_velocity))
       (send* _angular_velocity __angular_velocity)
     (progn
       (if __angular_velocity (setq _angular_velocity (car __angular_velocity)))
       _angular_velocity)))
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Vector3 _linear_velocity
    (send _linear_velocity :serialization-length)
    ;; geometry_msgs/Vector3 _angular_velocity
    (send _angular_velocity :serialization-length)
    ;; uint8 _mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Vector3 _linear_velocity
       (send _linear_velocity :serialize s)
     ;; geometry_msgs/Vector3 _angular_velocity
       (send _angular_velocity :serialize s)
     ;; uint8 _mode
       (write-byte _mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Vector3 _linear_velocity
     (send _linear_velocity :deserialize buf ptr-) (incf ptr- (send _linear_velocity :serialization-length))
   ;; geometry_msgs/Vector3 _angular_velocity
     (send _angular_velocity :deserialize buf ptr-) (incf ptr- (send _angular_velocity :serialization-length))
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ibvs_msgs::ControlCommand :md5sum-) "9308be7dd2b3f8e24e47b8a76ec696f5")
(setf (get ibvs_msgs::ControlCommand :datatype-) "ibvs_msgs/ControlCommand")
(setf (get ibvs_msgs::ControlCommand :definition-)
      "Header header

# Linear velocity command
geometry_msgs/Vector3 linear_velocity

# Angular velocity command
geometry_msgs/Vector3 angular_velocity

# Control mode
uint8 IBVS_MODE = 0
uint8 TRAJECTORY_MODE = 1
uint8 mode

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :ibvs_msgs/ControlCommand "9308be7dd2b3f8e24e47b8a76ec696f5")


