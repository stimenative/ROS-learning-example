#!/usr/bin/env python3

import rospy
from service_client_test.srv import intsum,intsumRequest,intsumResponse

# 建立回调函数
def doReq(req):
    # 处理数据并响应
    sum = req.num1 + req.num2
    # 创建响应
    resp = intsumResponse()
    resp.sum = sum
    rospy.loginfo("提交的数据为：num1=%d,num2=%d,sum=%d",req.num1,req.num2,resp.sum)
    return resp

if __name__ == "__main__":
    rospy.init_node("intsum_service")
    # 创建服务对象
    service = rospy.Service("intsum",intsum,doReq)
    # spin函数
    rospy.spin()