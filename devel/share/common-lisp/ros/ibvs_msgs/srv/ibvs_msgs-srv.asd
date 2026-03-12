
(cl:in-package :asdf)

(defsystem "ibvs_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "SetTarget" :depends-on ("_package_SetTarget"))
    (:file "_package_SetTarget" :depends-on ("_package"))
  ))