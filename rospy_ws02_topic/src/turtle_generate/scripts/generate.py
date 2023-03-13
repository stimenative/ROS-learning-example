#! /usr/bin/env python

import rospy
from turtlesim.srv import Spawn,SpawnResponse,SpawnRequest
import sys

if __name__ == "__main__":
    if len(sys.argv) != 5:
        rospy.logerr("请正确提交参数")
        sys.exit(1)
    
    rospy.init_node("generation")
    client = rospy.ServiceProxy("/spawn",Spawn)
    client.wait_for_service()
    request = SpawnRequest()
    request.x = float(sys.argv[1])
    request.y = float(sys.argv[2]) 
    request.theta = float(sys.argv[3])
    request.name = "new_turtle_" + str(sys.argv[4])
    try:
        response = client.call(request)
        rospy.loginfo("创建成功,乌龟名称为:%s",response.name)
    except Exception as id:
        print(id)
        rospy.loginfo("失败")