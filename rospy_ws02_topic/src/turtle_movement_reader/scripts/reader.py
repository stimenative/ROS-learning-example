#! /usr/bin/env python

import rospy
from turtlesim.msg import Pose

def doPose(data):
    rospy.loginfo("乌龟坐标为：%.3f,%.3f\n角度=%.3f\n线速度=%.3f\n角速度=%.3f",
                  data.x,data.y,data.theta,data.linear_velocity,data.angular_velocity)
    
if __name__ == "__main__":
    rospy.init_node("turtle_reader")
    reader = rospy.Subscriber("/turtle1/pose",Pose,doPose,queue_size=1000)
    rospy.spin()
