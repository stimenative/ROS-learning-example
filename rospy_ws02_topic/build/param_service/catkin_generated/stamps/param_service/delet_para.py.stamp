#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("delet_para")

    try:
        rospy.delete_param("para01_int")
    except Exception as e:
        # print(repr(e))
        rospy.loginfo("delete fail")