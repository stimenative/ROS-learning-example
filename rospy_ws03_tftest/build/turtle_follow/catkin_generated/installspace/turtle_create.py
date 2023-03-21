#!/usr/bin/env python3

import rospy
from turtlesim.srv import Spawn,SpawnRequest,SpawnResponse

if __name__ == "__main__":
    rospy.init_node("turtle_create")
    client = rospy.ServiceProxy("/spawn",Spawn)
    client.wait_for_service()
    request = SpawnRequest()
    request.x = 0.0
    request.y = 0.0
    request.theta = 3.14
    request.name = "turtle2"

    try:
        response = client.call(request)
        rospy.loginfo("success,turtle name is %s",response.name)
    except Exception as e:
        rospy.loginfo("fail")