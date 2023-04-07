#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "action_test/addintAction.h"

typedef actionlib::SimpleActionClient<action_test::addintAction> Client;

void do_callback(const actionlib::SimpleClientGoalState &state,const action_test::addintResultConstPtr &result)
{
    if (state.state_ == state.SUCCEEDED)
    {
        ROS_INFO("result:%d",result -> result);
    }
    else
    {
        ROS_INFO("fail");
    }
}

void active_callback()
{
    ROS_INFO("Server activated");
}

void do_feedback(const action_test::addintFeedbackConstPtr &feedback)
{
    ROS_INFO("current:%.2f",feedback -> progress);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"addint_client");
    ros::NodeHandle nh;
    Client client(nh,"addint",true);
    client.waitForServer();
    action_test::addintGoal goal;
    goal.num = 100;
    client.sendGoal(goal,&do_callback,&active_callback,&do_feedback);
    ros::spin();
    return 0;
}