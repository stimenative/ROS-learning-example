#! /usr/bin/env python

import rospy
import rosbag
from std_msgs.msg import String

if __name__ == "__main__":
    #初始化节点 
    rospy.init_node("read")

    # 创建 rosbag 对象
    bag = rosbag.Bag("../test.bag",'r')
    # 读数据
    bagMessage = bag.read_messages("chatter")
    for topic,msg,t in bagMessage:
        rospy.loginfo("%s,%s,%s",topic,msg,t)
    # 关闭流
    bag.close()
