#include "ros/ros.h"
#include "service_client_test/intsum.h"

bool doRequest(service_client_test::intsum::Request& request, 
    service_client_test::intsum::Response& response)
{
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("data:num1=%d,num2=%d",num1,num2);
    
    if (num1 < 0 || num2 < 0)
    {
        ROS_ERROR("wrong");
        return false;
    }
    response.sum = num1 + num2;
    return true;
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"service");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("intsum",doRequest);
    ROS_INFO("service started!");
    ros::spin();
    return 0;
}