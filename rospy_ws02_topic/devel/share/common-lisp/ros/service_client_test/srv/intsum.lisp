; Auto-generated. Do not edit!


(cl:in-package service_client_test-srv)


;//! \htmlinclude intsum-request.msg.html

(cl:defclass <intsum-request> (roslisp-msg-protocol:ros-message)
  ((num1
    :reader num1
    :initarg :num1
    :type cl:integer
    :initform 0)
   (num2
    :reader num2
    :initarg :num2
    :type cl:integer
    :initform 0))
)

(cl:defclass intsum-request (<intsum-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <intsum-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'intsum-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name service_client_test-srv:<intsum-request> is deprecated: use service_client_test-srv:intsum-request instead.")))

(cl:ensure-generic-function 'num1-val :lambda-list '(m))
(cl:defmethod num1-val ((m <intsum-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader service_client_test-srv:num1-val is deprecated.  Use service_client_test-srv:num1 instead.")
  (num1 m))

(cl:ensure-generic-function 'num2-val :lambda-list '(m))
(cl:defmethod num2-val ((m <intsum-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader service_client_test-srv:num2-val is deprecated.  Use service_client_test-srv:num2 instead.")
  (num2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <intsum-request>) ostream)
  "Serializes a message object of type '<intsum-request>"
  (cl:let* ((signed (cl:slot-value msg 'num1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'num2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <intsum-request>) istream)
  "Deserializes a message object of type '<intsum-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<intsum-request>)))
  "Returns string type for a service object of type '<intsum-request>"
  "service_client_test/intsumRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'intsum-request)))
  "Returns string type for a service object of type 'intsum-request"
  "service_client_test/intsumRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<intsum-request>)))
  "Returns md5sum for a message object of type '<intsum-request>"
  "4781436a0c2affec8025955a6041e481")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'intsum-request)))
  "Returns md5sum for a message object of type 'intsum-request"
  "4781436a0c2affec8025955a6041e481")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<intsum-request>)))
  "Returns full string definition for message of type '<intsum-request>"
  (cl:format cl:nil "# 请求~%int32 num1~%int32 num2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'intsum-request)))
  "Returns full string definition for message of type 'intsum-request"
  (cl:format cl:nil "# 请求~%int32 num1~%int32 num2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <intsum-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <intsum-request>))
  "Converts a ROS message object to a list"
  (cl:list 'intsum-request
    (cl:cons ':num1 (num1 msg))
    (cl:cons ':num2 (num2 msg))
))
;//! \htmlinclude intsum-response.msg.html

(cl:defclass <intsum-response> (roslisp-msg-protocol:ros-message)
  ((sum
    :reader sum
    :initarg :sum
    :type cl:integer
    :initform 0))
)

(cl:defclass intsum-response (<intsum-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <intsum-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'intsum-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name service_client_test-srv:<intsum-response> is deprecated: use service_client_test-srv:intsum-response instead.")))

(cl:ensure-generic-function 'sum-val :lambda-list '(m))
(cl:defmethod sum-val ((m <intsum-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader service_client_test-srv:sum-val is deprecated.  Use service_client_test-srv:sum instead.")
  (sum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <intsum-response>) ostream)
  "Serializes a message object of type '<intsum-response>"
  (cl:let* ((signed (cl:slot-value msg 'sum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <intsum-response>) istream)
  "Deserializes a message object of type '<intsum-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sum) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<intsum-response>)))
  "Returns string type for a service object of type '<intsum-response>"
  "service_client_test/intsumResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'intsum-response)))
  "Returns string type for a service object of type 'intsum-response"
  "service_client_test/intsumResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<intsum-response>)))
  "Returns md5sum for a message object of type '<intsum-response>"
  "4781436a0c2affec8025955a6041e481")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'intsum-response)))
  "Returns md5sum for a message object of type 'intsum-response"
  "4781436a0c2affec8025955a6041e481")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<intsum-response>)))
  "Returns full string definition for message of type '<intsum-response>"
  (cl:format cl:nil "# 响应~%int32 sum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'intsum-response)))
  "Returns full string definition for message of type 'intsum-response"
  (cl:format cl:nil "# 响应~%int32 sum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <intsum-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <intsum-response>))
  "Converts a ROS message object to a list"
  (cl:list 'intsum-response
    (cl:cons ':sum (sum msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'intsum)))
  'intsum-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'intsum)))
  'intsum-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'intsum)))
  "Returns string type for a service object of type '<intsum>"
  "service_client_test/intsum")