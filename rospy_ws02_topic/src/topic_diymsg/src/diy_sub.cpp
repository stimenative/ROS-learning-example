#include "ros/ros.h"
#include "topic_diymsg/Person.h"
#include <string>

typedef topic_diymsg::Person per;

void doperson(const per::ConstPtr& person_ptr)
{
    // auto name = person_ptr -> name.c_str();
    int age = person_ptr -> age;
    double height = person_ptr -> height;
    ROS_INFO("person info: %s, %d, %.2f",person_ptr -> name.c_str(),age,height);
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"sub_per");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<per>("person",10,doperson);
    ros::spin();
    return 0;
}