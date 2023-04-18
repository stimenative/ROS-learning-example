#include "ros/ros.h"
#include "service_client_test/intsum.h"

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    if (argc != 3 && argc != 5)
    {
        ROS_ERROR("wrong arg");
        return 1;
    }
    ros::init(argc,argv,"client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<service_client_test::intsum>("intsum");
    ros::service::waitForService("intsum");
    
    service_client_test::intsum number;
    number.request.num1 = atoi(argv[1]);
    number.request.num2 = atoi(argv[2]);
    
    bool flag = client.call(number);
    if (flag)
    {
        ROS_INFO("num1=%d,num2=%d,num1+num2=%d",number.request.num1,number.request.num2,number.response.sum);
    }
    else
    {
        ROS_INFO("wrong");
        return 1;
    }
    return 0;
}