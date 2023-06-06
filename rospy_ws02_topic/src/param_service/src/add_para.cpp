#include "ros/ros.h"

int main(int argc,char *argv[])
{
    ros::init(argc,argv,"set_update_param");

    std::vector<std::string> students;
    students.push_back("zhangsan");
    students.push_back("lisi");
    students.push_back("wangwu");
    
    std::map<std::string,std::string> friends;
    friends["guo"]="huang";
    friends["yuang"]="xiao";

    ros::NodeHandle nh;
    nh.setParam("nh_int",10);
    nh.setParam("nh_double",3.14);
    nh.setParam("nh_bool",true);
    nh.setParam("nh_vector",students);
    nh.setParam("nh_map",friends);

    return 0;
}