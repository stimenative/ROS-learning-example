#!/usr/bin/env python3

import rospy

rightnow = rospy.Time.now()

rospy.loginfo("当前时间为：%.2f",rightnow)