#! /usr/bin/env python

import rospy
import actionlib
from action_test.msg import addintAction,addintFeedback,addintResult

class ActionServer:
    def __init__(self):
        self.server = actionlib.SimpleActionServer("addint",addintAction,self.callback,False)
        self.server.start()
        rospy.loginfo("start")

    def callback(self,goal):
        rospy.loginfo("request:")
        num = goal.num
        rate = rospy.Rate(10)
        sum = 0
        for i in range(1,num + 1):
            sum = sum + i
            feedback = i / num
            rospy.loginfo("now:%.2f",feedback)
            obj_feedback = addintFeedback()
            obj_feedback.progress = feedback
            self.server.publish_feedback(obj_feedback)
            rate.sleep()
        result = addintResult()
        result.result = sum
        self.server.set_succeeded(result)
        rospy.loginfo("result:%d",sum)

if __name__ == "__main__":
    rospy.init_node("action_test_server")
    server = ActionServer()
    rospy.spin()