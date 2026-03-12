
(cl:in-package :asdf)

(defsystem "ibvs_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ControlCommand" :depends-on ("_package_ControlCommand"))
    (:file "_package_ControlCommand" :depends-on ("_package"))
    (:file "ImageFeatures" :depends-on ("_package_ImageFeatures"))
    (:file "_package_ImageFeatures" :depends-on ("_package"))
    (:file "TargetState" :depends-on ("_package_TargetState"))
    (:file "_package_TargetState" :depends-on ("_package"))
    (:file "TrajectoryPoint" :depends-on ("_package_TrajectoryPoint"))
    (:file "_package_TrajectoryPoint" :depends-on ("_package"))
  ))