#!/usr/bin/env python3

'''
    topic:/turtle1/pose (Pose) ---> __node:"dynamic_pub" p: tf_data (TransformStamped)__ ---> node:"dynamic_sub"
'''
import rospy
from turtlesim.msg import Pose
import tf2_ros
from geometry_msgs.msg import TransformStamped
import tf.transformations

def doPose(pose):
    broadcaster = tf2_ros.TransformBroadcaster()
    tf_data = TransformStamped()
    tf_data.header.frame_id = "base"
    tf_data.header.stamp = rospy.Time.now()
    tf_data.child_frame_id = "turtle1"
    tf_data.transform.translation.x = pose.x
    tf_data.transform.translation.y = pose.y
    tf_data.transform.translation.z = 0.0
    qtn = tf.transformations.quaternion_from_euler(0,0,pose.theta)
    tf_data.transform.rotation.x = qtn[0]
    tf_data.transform.rotation.y = qtn[1]
    tf_data.transform.rotation.z = qtn[2]
    tf_data.transform.rotation.w = qtn[3]
    broadcaster.sendTransform(tf_data)
    
if __name__ == "__main__":
    rospy.init_node("dynamic_pub")
    sub = rospy.Subscriber("/turtle1/pose",Pose,doPose)
    rospy.spin()