;; Auto-generated. Do not edit!


(when (boundp 'ibvs_msgs::TargetState)
  (if (not (find-package "IBVS_MSGS"))
    (make-package "IBVS_MSGS"))
  (shadow 'TargetState (find-package "IBVS_MSGS")))
(unless (find-package "IBVS_MSGS::TARGETSTATE")
  (make-package "IBVS_MSGS::TARGETSTATE"))

(in-package "ROS")
;;//! \htmlinclude TargetState.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ibvs_msgs::TargetState
  :super ros::object
  :slots (_header _u _v _u_dot _v_dot _depth _position _velocity _confidence ))

(defmethod ibvs_msgs::TargetState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:u __u) 0.0)
    ((:v __v) 0.0)
    ((:u_dot __u_dot) 0.0)
    ((:v_dot __v_dot) 0.0)
    ((:depth __depth) 0.0)
    ((:position __position) (instance geometry_msgs::Point :init))
    ((:velocity __velocity) (instance geometry_msgs::Vector3 :init))
    ((:confidence __confidence) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _u (float __u))
   (setq _v (float __v))
   (setq _u_dot (float __u_dot))
   (setq _v_dot (float __v_dot))
   (setq _depth (float __depth))
   (setq _position __position)
   (setq _velocity __velocity)
   (setq _confidence (float __confidence))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:u
   (&optional __u)
   (if __u (setq _u __u)) _u)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:u_dot
   (&optional __u_dot)
   (if __u_dot (setq _u_dot __u_dot)) _u_dot)
  (:v_dot
   (&optional __v_dot)
   (if __v_dot (setq _v_dot __v_dot)) _v_dot)
  (:depth
   (&optional __depth)
   (if __depth (setq _depth __depth)) _depth)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:velocity
   (&rest __velocity)
   (if (keywordp (car __velocity))
       (send* _velocity __velocity)
     (progn
       (if __velocity (setq _velocity (car __velocity)))
       _velocity)))
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _u
    8
    ;; float64 _v
    8
    ;; float64 _u_dot
    8
    ;; float64 _v_dot
    8
    ;; float64 _depth
    8
    ;; geometry_msgs/Point _position
    (send _position :serialization-length)
    ;; geometry_msgs/Vector3 _velocity
    (send _velocity :serialization-length)
    ;; float64 _confidence
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _u
       (sys::poke _u (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v
       (sys::poke _v (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _u_dot
       (sys::poke _u_dot (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v_dot
       (sys::poke _v_dot (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _depth
       (sys::poke _depth (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; geometry_msgs/Point _position
       (send _position :serialize s)
     ;; geometry_msgs/Vector3 _velocity
       (send _velocity :serialize s)
     ;; float64 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _u
     (setq _u (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v
     (setq _v (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _u_dot
     (setq _u_dot (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v_dot
     (setq _v_dot (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _depth
     (setq _depth (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; geometry_msgs/Point _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; geometry_msgs/Vector3 _velocity
     (send _velocity :deserialize buf ptr-) (incf ptr- (send _velocity :serialization-length))
   ;; float64 _confidence
     (setq _confidence (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get ibvs_msgs::TargetState :md5sum-) "c444884cd08771ae2c8b2dd3de8f1d9a")
(setf (get ibvs_msgs::TargetState :datatype-) "ibvs_msgs/TargetState")
(setf (get ibvs_msgs::TargetState :definition-)
      "Header header

# Target position in image coordinates
float64 u
float64 v

# Target velocity in image plane
float64 u_dot
float64 v_dot

# Target depth (distance from camera)
float64 depth

# Target 3D position in camera frame
geometry_msgs/Point position

# Target 3D velocity in camera frame
geometry_msgs/Vector3 velocity

# Confidence score
float64 confidence

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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



(provide :ibvs_msgs/TargetState "c444884cd08771ae2c8b2dd3de8f1d9a")


