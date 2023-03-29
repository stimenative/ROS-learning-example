#! /usr/bin/env python

import rospy
import rosbag
from std_msgs.msg import String

if __name__ == "__main__":
    rospy.init_node("write")
    bag = rosbag.Bag("../test.bag","w")
    s = String()
    s.data = "gwqgwq"

    bag.write = ("chatter",s)
    bag.write = ("chatter",s)
    bag.write = ("chatter",s)

    bag.close()
