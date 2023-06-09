#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "action_test/addintAction.h"

/*
    创建两个节点，客户端向服务端发送目标数据N:int
    服务端计算1～N之间的和，返回给客户端
    每累加一次耗时0.1s
    每累加一次给客户端响应一次执行进度
*/

typedef actionlib::SimpleActionServer<action_test::addintAction> Server;

void callback(const action_test::addintGoalConstPtr &goal,Server* server)
{
    int goalnum = goal -> num;
    ROS_INFO("目标值：%d",goalnum);
    int result = 0;
    action_test::addintFeedback feedback;
    ros::Rate rate(10);
    for (int i = 1; i <= goalnum; i++)
    {
        result += i;
        feedback.progress = i / (double)goalnum;
        server -> publishFeedback(feedback);
        rate.sleep();
    }
    action_test::addintResult r;
    r.result = result;
    server -> setSucceeded(r);
    ROS_INFO("最终结果：%d",r.result);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("action服务端");
    ros::init(argc,argv,"addint_server");
    ros::NodeHandle nh;
    Server server(nh,"addint",boost::bind(&callback,_1,&server),false);
    server.start();
    ros::spin();
    return 0;
}