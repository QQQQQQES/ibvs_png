;; Auto-generated. Do not edit!


(when (boundp 'ibvs_msgs::SetTarget)
  (if (not (find-package "IBVS_MSGS"))
    (make-package "IBVS_MSGS"))
  (shadow 'SetTarget (find-package "IBVS_MSGS")))
(unless (find-package "IBVS_MSGS::SETTARGET")
  (make-package "IBVS_MSGS::SETTARGET"))
(unless (find-package "IBVS_MSGS::SETTARGETREQUEST")
  (make-package "IBVS_MSGS::SETTARGETREQUEST"))
(unless (find-package "IBVS_MSGS::SETTARGETRESPONSE")
  (make-package "IBVS_MSGS::SETTARGETRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass ibvs_msgs::SetTargetRequest
  :super ros::object
  :slots (_target_id _initial_position ))

(defmethod ibvs_msgs::SetTargetRequest
  (:init
   (&key
    ((:target_id __target_id) 0)
    ((:initial_position __initial_position) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _target_id (round __target_id))
   (setq _initial_position __initial_position)
   self)
  (:target_id
   (&optional __target_id)
   (if __target_id (setq _target_id __target_id)) _target_id)
  (:initial_position
   (&rest __initial_position)
   (if (keywordp (car __initial_position))
       (send* _initial_position __initial_position)
     (progn
       (if __initial_position (setq _initial_position (car __initial_position)))
       _initial_position)))
  (:serialization-length
   ()
   (+
    ;; int32 _target_id
    4
    ;; geometry_msgs/Point _initial_position
    (send _initial_position :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _target_id
       (write-long _target_id s)
     ;; geometry_msgs/Point _initial_position
       (send _initial_position :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _target_id
     (setq _target_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Point _initial_position
     (send _initial_position :deserialize buf ptr-) (incf ptr- (send _initial_position :serialization-length))
   ;;
   self)
  )

(defclass ibvs_msgs::SetTargetResponse
  :super ros::object
  :slots (_success _message ))

(defmethod ibvs_msgs::SetTargetResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _message (string __message))
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass ibvs_msgs::SetTarget
  :super ros::object
  :slots ())

(setf (get ibvs_msgs::SetTarget :md5sum-) "8cbd1dafdc9b76449a121f5401ae556d")
(setf (get ibvs_msgs::SetTarget :datatype-) "ibvs_msgs/SetTarget")
(setf (get ibvs_msgs::SetTarget :request) ibvs_msgs::SetTargetRequest)
(setf (get ibvs_msgs::SetTarget :response) ibvs_msgs::SetTargetResponse)

(defmethod ibvs_msgs::SetTargetRequest
  (:response () (instance ibvs_msgs::SetTargetResponse :init)))

(setf (get ibvs_msgs::SetTargetRequest :md5sum-) "8cbd1dafdc9b76449a121f5401ae556d")
(setf (get ibvs_msgs::SetTargetRequest :datatype-) "ibvs_msgs/SetTargetRequest")
(setf (get ibvs_msgs::SetTargetRequest :definition-)
      "# Request
int32 target_id
geometry_msgs/Point initial_position

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
# Response
bool success
string message

")

(setf (get ibvs_msgs::SetTargetResponse :md5sum-) "8cbd1dafdc9b76449a121f5401ae556d")
(setf (get ibvs_msgs::SetTargetResponse :datatype-) "ibvs_msgs/SetTargetResponse")
(setf (get ibvs_msgs::SetTargetResponse :definition-)
      "# Request
int32 target_id
geometry_msgs/Point initial_position

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
# Response
bool success
string message

")



(provide :ibvs_msgs/SetTarget "8cbd1dafdc9b76449a121f5401ae556d")


