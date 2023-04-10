#include <pluginlib/class_loader.h>
#include <pluginlib_test/polygon_base.h>

int main(int argc,char** argv)
{
    pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("pluginlib_test","polygon_base::RegularPolygon");

    try
    {
        boost::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createInstance("polygon_plugins::Triangle");
        triangle -> initialize(10.0);

        boost::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createInstance("polygon_plugins::Square");
        square -> initialize(10.0);

        ROS_INFO("triangle area:%.2f",triangle -> area());
        ROS_INFO("square area:%.2f",square -> area());
    }
    catch(pluginlib::PluginlibException& ex)
    {
        ROS_ERROR("failed to load. Error:%s",ex.what());
    }

    return 0;
}