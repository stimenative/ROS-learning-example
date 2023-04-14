#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"publisher");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<std_msgs::String>("topic_comu",10);
    std_msgs::String message;
    std::string message_front = "hello";
    int count = 0;
    ros::Rate r(1);

    while (ros::ok())
    {
        std::stringstream ss;
        ss << message_front << count;
        message.data = ss.str();
        pub.publish(message);
        ROS_INFO("message:%s",message.data.c_str());

        r.sleep();
        count++;
        ros::spinOnce;
    }
    return 0;
}