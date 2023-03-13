
(cl:in-package :asdf)

(defsystem "service_client_test-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "intsum" :depends-on ("_package_intsum"))
    (:file "_package_intsum" :depends-on ("_package"))
  ))