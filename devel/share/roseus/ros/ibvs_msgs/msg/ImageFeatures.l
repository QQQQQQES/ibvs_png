;; Auto-generated. Do not edit!


(when (boundp 'ibvs_msgs::ImageFeatures)
  (if (not (find-package "IBVS_MSGS"))
    (make-package "IBVS_MSGS"))
  (shadow 'ImageFeatures (find-package "IBVS_MSGS")))
(unless (find-package "IBVS_MSGS::IMAGEFEATURES")
  (make-package "IBVS_MSGS::IMAGEFEATURES"))

(in-package "ROS")
;;//! \htmlinclude ImageFeatures.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ibvs_msgs::ImageFeatures
  :super ros::object
  :slots (_header _feature_points _feature_velocities _image_jacobian _num_features ))

(defmethod ibvs_msgs::ImageFeatures
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:feature_points __feature_points) ())
    ((:feature_velocities __feature_velocities) ())
    ((:image_jacobian __image_jacobian) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:num_features __num_features) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _feature_points __feature_points)
   (setq _feature_velocities __feature_velocities)
   (setq _image_jacobian __image_jacobian)
   (setq _num_features (round __num_features))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:feature_points
   (&rest __feature_points)
   (if (keywordp (car __feature_points))
       (send* _feature_points __feature_points)
     (progn
       (if __feature_points (setq _feature_points (car __feature_points)))
       _feature_points)))
  (:feature_velocities
   (&rest __feature_velocities)
   (if (keywordp (car __feature_velocities))
       (send* _feature_velocities __feature_velocities)
     (progn
       (if __feature_velocities (setq _feature_velocities (car __feature_velocities)))
       _feature_velocities)))
  (:image_jacobian
   (&optional __image_jacobian)
   (if __image_jacobian (setq _image_jacobian __image_jacobian)) _image_jacobian)
  (:num_features
   (&optional __num_features)
   (if __num_features (setq _num_features __num_features)) _num_features)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[] _feature_points
    (apply #'+ (send-all _feature_points :serialization-length)) 4
    ;; geometry_msgs/Vector3[] _feature_velocities
    (apply #'+ (send-all _feature_velocities :serialization-length)) 4
    ;; float64[] _image_jacobian
    (* 8    (length _image_jacobian)) 4
    ;; int32 _num_features
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[] _feature_points
     (write-long (length _feature_points) s)
     (dolist (elem _feature_points)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Vector3[] _feature_velocities
     (write-long (length _feature_velocities) s)
     (dolist (elem _feature_velocities)
       (send elem :serialize s)
       )
     ;; float64[] _image_jacobian
     (write-long (length _image_jacobian) s)
     (dotimes (i (length _image_jacobian))
       (sys::poke (elt _image_jacobian i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; int32 _num_features
       (write-long _num_features s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[] _feature_points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _feature_points (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _feature_points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Vector3[] _feature_velocities
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _feature_velocities (let (r) (dotimes (i n) (push (instance geometry_msgs::Vector3 :init) r)) r))
     (dolist (elem- _feature_velocities)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float64[] _image_jacobian
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _image_jacobian (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _image_jacobian i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; int32 _num_features
     (setq _num_features (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ibvs_msgs::ImageFeatures :md5sum-) "91c151d3e6d430698eaca9cd7aafd529")
(setf (get ibvs_msgs::ImageFeatures :datatype-) "ibvs_msgs/ImageFeatures")
(setf (get ibvs_msgs::ImageFeatures :definition-)
      "Header header

# Image feature points
geometry_msgs/Point[] feature_points

# Feature velocities
geometry_msgs/Vector3[] feature_velocities

# Image Jacobian matrix (flattened)
float64[] image_jacobian

# Number of features
int32 num_features

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



(provide :ibvs_msgs/ImageFeatures "91c151d3e6d430698eaca9cd7aafd529")


