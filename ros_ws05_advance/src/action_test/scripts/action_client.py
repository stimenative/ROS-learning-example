#! /usr/bin/env python

import rospy
import actionlib
from action_test.msg import addintAction,addintGoal

def do_callback(state,result):
    if state == actionlib.GoalStatus.SUCCEEDED:
        rospy.loginfo("result:%d",result.result)

def active_callback():
    rospy.loginfo("Server Activated")

def do_feedback(feedback):
    rospy.loginfo("Now:%.2f",feedback.progress)

if __name__ == "__main__":
    rospy.init_node("addint_client")
    client = actionlib.SimpleActionClient("addint",addintAction)
    client.wait_for_server()
    obj_goal = addintGoal()
    obj_goal.num = 100
    client.send_goal(obj_goal,do_callback,active_callback,do_feedback)
    rospy.spin()