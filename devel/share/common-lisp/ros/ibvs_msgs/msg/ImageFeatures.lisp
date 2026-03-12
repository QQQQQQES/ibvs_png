; Auto-generated. Do not edit!


(cl:in-package ibvs_msgs-msg)


;//! \htmlinclude ImageFeatures.msg.html

(cl:defclass <ImageFeatures> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (feature_points
    :reader feature_points
    :initarg :feature_points
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (feature_velocities
    :reader feature_velocities
    :initarg :feature_velocities
    :type (cl:vector geometry_msgs-msg:Vector3)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Vector3 :initial-element (cl:make-instance 'geometry_msgs-msg:Vector3)))
   (image_jacobian
    :reader image_jacobian
    :initarg :image_jacobian
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (num_features
    :reader num_features
    :initarg :num_features
    :type cl:integer
    :initform 0))
)

(cl:defclass ImageFeatures (<ImageFeatures>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ImageFeatures>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ImageFeatures)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ibvs_msgs-msg:<ImageFeatures> is deprecated: use ibvs_msgs-msg:ImageFeatures instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ImageFeatures>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-msg:header-val is deprecated.  Use ibvs_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'feature_points-val :lambda-list '(m))
(cl:defmethod feature_points-val ((m <ImageFeatures>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-msg:feature_points-val is deprecated.  Use ibvs_msgs-msg:feature_points instead.")
  (feature_points m))

(cl:ensure-generic-function 'feature_velocities-val :lambda-list '(m))
(cl:defmethod feature_velocities-val ((m <ImageFeatures>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-msg:feature_velocities-val is deprecated.  Use ibvs_msgs-msg:feature_velocities instead.")
  (feature_velocities m))

(cl:ensure-generic-function 'image_jacobian-val :lambda-list '(m))
(cl:defmethod image_jacobian-val ((m <ImageFeatures>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-msg:image_jacobian-val is deprecated.  Use ibvs_msgs-msg:image_jacobian instead.")
  (image_jacobian m))

(cl:ensure-generic-function 'num_features-val :lambda-list '(m))
(cl:defmethod num_features-val ((m <ImageFeatures>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-msg:num_features-val is deprecated.  Use ibvs_msgs-msg:num_features instead.")
  (num_features m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ImageFeatures>) ostream)
  "Serializes a message object of type '<ImageFeatures>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'feature_points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'feature_points))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'feature_velocities))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'feature_velocities))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'image_jacobian))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'image_jacobian))
  (cl:let* ((signed (cl:slot-value msg 'num_features)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ImageFeatures>) istream)
  "Deserializes a message object of type '<ImageFeatures>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'feature_points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'feature_points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'feature_velocities) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'feature_velocities)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Vector3))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'image_jacobian) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'image_jacobian)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num_features) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ImageFeatures>)))
  "Returns string type for a message object of type '<ImageFeatures>"
  "ibvs_msgs/ImageFeatures")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ImageFeatures)))
  "Returns string type for a message object of type 'ImageFeatures"
  "ibvs_msgs/ImageFeatures")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ImageFeatures>)))
  "Returns md5sum for a message object of type '<ImageFeatures>"
  "91c151d3e6d430698eaca9cd7aafd529")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ImageFeatures)))
  "Returns md5sum for a message object of type 'ImageFeatures"
  "91c151d3e6d430698eaca9cd7aafd529")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ImageFeatures>)))
  "Returns full string definition for message of type '<ImageFeatures>"
  (cl:format cl:nil "Header header~%~%# Image feature points~%geometry_msgs/Point[] feature_points~%~%# Feature velocities~%geometry_msgs/Vector3[] feature_velocities~%~%# Image Jacobian matrix (flattened)~%float64[] image_jacobian~%~%# Number of features~%int32 num_features~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ImageFeatures)))
  "Returns full string definition for message of type 'ImageFeatures"
  (cl:format cl:nil "Header header~%~%# Image feature points~%geometry_msgs/Point[] feature_points~%~%# Feature velocities~%geometry_msgs/Vector3[] feature_velocities~%~%# Image Jacobian matrix (flattened)~%float64[] image_jacobian~%~%# Number of features~%int32 num_features~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ImageFeatures>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'feature_points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'feature_velocities) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'image_jacobian) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ImageFeatures>))
  "Converts a ROS message object to a list"
  (cl:list 'ImageFeatures
    (cl:cons ':header (header msg))
    (cl:cons ':feature_points (feature_points msg))
    (cl:cons ':feature_velocities (feature_velocities msg))
    (cl:cons ':image_jacobian (image_jacobian msg))
    (cl:cons ':num_features (num_features msg))
))
