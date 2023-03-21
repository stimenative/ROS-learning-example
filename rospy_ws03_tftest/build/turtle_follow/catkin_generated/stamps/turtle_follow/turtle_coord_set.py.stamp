#! /usr/bin/env python

'''
    根据两乌龟的pose信息,生成坐标系
'''

import rospy
import sys
from turtlesim.msg import Pose
from geometry_msgs.msg import TransformStamped
import tf2_ros
import tf.transformations

turtle_name = ""

def doPose(pose):
    broadcaster = tf2_ros.TransformBroadcaster()
    tfs = TransformStamped()
    tfs.header.frame_id = "base"
    tfs.header.stamp = rospy.Time.now()
    
    tfs.child_frame_id = turtle_name
    tfs.transform.translation.x = pose.x
    tfs.transform.translation.y = pose.y
    tfs.transform.translation.z = 0.0

    qtn = tf.transformations.quaternion_from_euler(0,0,pose.theta)
    tfs.transform.rotation.x = qtn[0]
    tfs.transform.rotation.y = qtn[1]
    tfs.transform.rotation.z = qtn[2]
    tfs.transform.rotation.w = qtn[3]

    broadcaster.sendTransform(tfs)

if __name__ == "__main__":
    rospy.init_node("coord_pub")
    rospy.loginfo("----%d",len(sys.argv))
    if len(sys.argv) < 2:
        rospy.loginfo("please enter turtle's namespace!")
    else:
        turtle_name = sys.argv[1]
    rospy.loginfo("turtle name: %s",turtle_name)

    rospy.Subscriber(turtle_name+"/pose",Pose,doPose)
    rospy.spin()