; Auto-generated. Do not edit!


(cl:in-package ibvs_msgs-srv)


;//! \htmlinclude SetTarget-request.msg.html

(cl:defclass <SetTarget-request> (roslisp-msg-protocol:ros-message)
  ((target_id
    :reader target_id
    :initarg :target_id
    :type cl:integer
    :initform 0)
   (initial_position
    :reader initial_position
    :initarg :initial_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass SetTarget-request (<SetTarget-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTarget-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTarget-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ibvs_msgs-srv:<SetTarget-request> is deprecated: use ibvs_msgs-srv:SetTarget-request instead.")))

(cl:ensure-generic-function 'target_id-val :lambda-list '(m))
(cl:defmethod target_id-val ((m <SetTarget-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-srv:target_id-val is deprecated.  Use ibvs_msgs-srv:target_id instead.")
  (target_id m))

(cl:ensure-generic-function 'initial_position-val :lambda-list '(m))
(cl:defmethod initial_position-val ((m <SetTarget-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-srv:initial_position-val is deprecated.  Use ibvs_msgs-srv:initial_position instead.")
  (initial_position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTarget-request>) ostream)
  "Serializes a message object of type '<SetTarget-request>"
  (cl:let* ((signed (cl:slot-value msg 'target_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'initial_position) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTarget-request>) istream)
  "Deserializes a message object of type '<SetTarget-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'initial_position) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTarget-request>)))
  "Returns string type for a service object of type '<SetTarget-request>"
  "ibvs_msgs/SetTargetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTarget-request)))
  "Returns string type for a service object of type 'SetTarget-request"
  "ibvs_msgs/SetTargetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTarget-request>)))
  "Returns md5sum for a message object of type '<SetTarget-request>"
  "8cbd1dafdc9b76449a121f5401ae556d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTarget-request)))
  "Returns md5sum for a message object of type 'SetTarget-request"
  "8cbd1dafdc9b76449a121f5401ae556d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTarget-request>)))
  "Returns full string definition for message of type '<SetTarget-request>"
  (cl:format cl:nil "# Request~%int32 target_id~%geometry_msgs/Point initial_position~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTarget-request)))
  "Returns full string definition for message of type 'SetTarget-request"
  (cl:format cl:nil "# Request~%int32 target_id~%geometry_msgs/Point initial_position~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTarget-request>))
  (cl:+ 0
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'initial_position))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTarget-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTarget-request
    (cl:cons ':target_id (target_id msg))
    (cl:cons ':initial_position (initial_position msg))
))
;//! \htmlinclude SetTarget-response.msg.html

(cl:defclass <SetTarget-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass SetTarget-response (<SetTarget-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTarget-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTarget-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ibvs_msgs-srv:<SetTarget-response> is deprecated: use ibvs_msgs-srv:SetTarget-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetTarget-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-srv:success-val is deprecated.  Use ibvs_msgs-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <SetTarget-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ibvs_msgs-srv:message-val is deprecated.  Use ibvs_msgs-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTarget-response>) ostream)
  "Serializes a message object of type '<SetTarget-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTarget-response>) istream)
  "Deserializes a message object of type '<SetTarget-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTarget-response>)))
  "Returns string type for a service object of type '<SetTarget-response>"
  "ibvs_msgs/SetTargetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTarget-response)))
  "Returns string type for a service object of type 'SetTarget-response"
  "ibvs_msgs/SetTargetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTarget-response>)))
  "Returns md5sum for a message object of type '<SetTarget-response>"
  "8cbd1dafdc9b76449a121f5401ae556d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTarget-response)))
  "Returns md5sum for a message object of type 'SetTarget-response"
  "8cbd1dafdc9b76449a121f5401ae556d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTarget-response>)))
  "Returns full string definition for message of type '<SetTarget-response>"
  (cl:format cl:nil "# Response~%bool success~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTarget-response)))
  "Returns full string definition for message of type 'SetTarget-response"
  (cl:format cl:nil "# Response~%bool success~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTarget-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTarget-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTarget-response
    (cl:cons ':success (success msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetTarget)))
  'SetTarget-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetTarget)))
  'SetTarget-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTarget)))
  "Returns string type for a service object of type '<SetTarget>"
  "ibvs_msgs/SetTarget")