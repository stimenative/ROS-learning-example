#include "ros/ros.h"
#include "topic_diymsg/Person.h"

typedef topic_diymsg::Person per;

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"pub_person");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<per>("person",10);
    per p;
    p.age = 10;
    p.height = 180;
    p.name = "lw";
    
    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(p);
        p.age ++;
        ROS_INFO("name:%s,age:%d,height:%.2f",p.name,p.age,p.height);
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}