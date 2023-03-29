#!/usr/bin/env python3

import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped,Twist
import math

if __name__ == "__main__":
    rospy.init_node("turtle_follow_controler")
    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(10)
    pub = rospy.Publisher("/turtle2/cmd_vel",Twist,queue_size=1000)

    while not rospy.is_shutdown():
        rate.sleep()
        try:
            trans = buffer.lookup_transform("turtle2","turtle1",rospy.Duration(0))
            twist_info = Twist()
            x = trans.transform.translation.x
            y = trans.transform.translation.y
            twist_info.linear.x = 0.5 * math.sqrt(math.pow(x,2) + math.pow(y,2))
            twist_info.angular.z = 4 * math.atan2(y,x)
            pub.publish(twist_info)

        except Exception as e:
            rospy.logwarn("%s",e)