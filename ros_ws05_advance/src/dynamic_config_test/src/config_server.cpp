#include "ros/ros.h"
#include "dynamic_config_test/drConfig.h"
#include "dynamic_reconfigure/server.h"

void callback(dynamic_config_test::drConfig& config, uint32_t level)
{
    ROS_INFO("dynamic data:%d,%.2f,%d,%s,%d",
    config.int_param,
    config.double_param,
    config.bool_param,
    config.string_param.c_str(),
    config.list_param);
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"dr");
    dynamic_reconfigure::Server<dynamic_config_test::drConfig> server;
    dynamic_reconfigure::Server<dynamic_config_test::drConfig>::CallbackType cbtype;
    cbtype = boost::bind(&callback,_1,_2);
    server.setCallback(cbtype);
    ros::spin();
    return 0;
}