#include "ros/ros.h"
#include "std_msgs/String.h"

void do_msg(const std_msgs::String::ConstPtr& msg_ptr)
{
    ROS_INFO("I heard: %s",msg_ptr -> data.c_str());
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"subscripter");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("topic_comu",10,do_msg);
    ros::spin();
    return 0;
}