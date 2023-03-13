;; Auto-generated. Do not edit!


(when (boundp 'service_client_test::intsum)
  (if (not (find-package "SERVICE_CLIENT_TEST"))
    (make-package "SERVICE_CLIENT_TEST"))
  (shadow 'intsum (find-package "SERVICE_CLIENT_TEST")))
(unless (find-package "SERVICE_CLIENT_TEST::INTSUM")
  (make-package "SERVICE_CLIENT_TEST::INTSUM"))
(unless (find-package "SERVICE_CLIENT_TEST::INTSUMREQUEST")
  (make-package "SERVICE_CLIENT_TEST::INTSUMREQUEST"))
(unless (find-package "SERVICE_CLIENT_TEST::INTSUMRESPONSE")
  (make-package "SERVICE_CLIENT_TEST::INTSUMRESPONSE"))

(in-package "ROS")





(defclass service_client_test::intsumRequest
  :super ros::object
  :slots (_num1 _num2 ))

(defmethod service_client_test::intsumRequest
  (:init
   (&key
    ((:num1 __num1) 0)
    ((:num2 __num2) 0)
    )
   (send-super :init)
   (setq _num1 (round __num1))
   (setq _num2 (round __num2))
   self)
  (:num1
   (&optional __num1)
   (if __num1 (setq _num1 __num1)) _num1)
  (:num2
   (&optional __num2)
   (if __num2 (setq _num2 __num2)) _num2)
  (:serialization-length
   ()
   (+
    ;; int32 _num1
    4
    ;; int32 _num2
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _num1
       (write-long _num1 s)
     ;; int32 _num2
       (write-long _num2 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _num1
     (setq _num1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _num2
     (setq _num2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass service_client_test::intsumResponse
  :super ros::object
  :slots (_sum ))

(defmethod service_client_test::intsumResponse
  (:init
   (&key
    ((:sum __sum) 0)
    )
   (send-super :init)
   (setq _sum (round __sum))
   self)
  (:sum
   (&optional __sum)
   (if __sum (setq _sum __sum)) _sum)
  (:serialization-length
   ()
   (+
    ;; int32 _sum
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _sum
       (write-long _sum s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _sum
     (setq _sum (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass service_client_test::intsum
  :super ros::object
  :slots ())

(setf (get service_client_test::intsum :md5sum-) "4781436a0c2affec8025955a6041e481")
(setf (get service_client_test::intsum :datatype-) "service_client_test/intsum")
(setf (get service_client_test::intsum :request) service_client_test::intsumRequest)
(setf (get service_client_test::intsum :response) service_client_test::intsumResponse)

(defmethod service_client_test::intsumRequest
  (:response () (instance service_client_test::intsumResponse :init)))

(setf (get service_client_test::intsumRequest :md5sum-) "4781436a0c2affec8025955a6041e481")
(setf (get service_client_test::intsumRequest :datatype-) "service_client_test/intsumRequest")
(setf (get service_client_test::intsumRequest :definition-)
      "# 请求
int32 num1
int32 num2
---
# 响应
int32 sum
")

(setf (get service_client_test::intsumResponse :md5sum-) "4781436a0c2affec8025955a6041e481")
(setf (get service_client_test::intsumResponse :datatype-) "service_client_test/intsumResponse")
(setf (get service_client_test::intsumResponse :definition-)
      "# 请求
int32 num1
int32 num2
---
# 响应
int32 sum
")



(provide :service_client_test/intsum "4781436a0c2affec8025955a6041e481")


