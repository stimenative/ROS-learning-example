#include "nodelet/nodelet.h"
#include "pluginlib/class_list_macros.h"
#include "ros/ros.h"
#include "std_msgs/Float64.h"

namespace nodelet_test_ns
{
    class Myplus: public nodelet::Nodelet {
        public:
        Myplus(){
            value = 0.0;
        }

        void onInit(){
            ros::NodeHandle& nh = getPrivateNodeHandle();
            nh.getParam("value",value);
            pub = nh.advertise<std_msgs::Float64>("out",100);
            sub = nh.subscribe<std_msgs::Float64>("in",100,&Myplus::docallback,this);
        }

        void docallback(const std_msgs::Float64::ConstPtr& p){
            double num = p-> data;
            double result = num + value;
            std_msgs::Float64 r;
            r.data = result;
            pub.publish(r);
        }
        
        private:
        ros::Publisher pub;
        ros::Subscriber sub;
        double value;
    };
}
PLUGINLIB_EXPORT_CLASS(nodelet_test_ns::Myplus,nodelet::Nodelet)