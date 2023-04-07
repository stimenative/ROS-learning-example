#! /usr/bin/env python

import rospy
from dynamic_reconfigure.server import Server
from dynamic_config_test.cfg import drConfig


def callback(config, level):
    rospy.loginfo(
        "dynamic param:%d,%.2f,%d,%s,%d",
        config.int_param,
        config.double_param,
        config.bool_param,
        config.string_param,
        config.list_param,
    )
    return config


if __name__ == "__main__":
    rospy.init_node("dynamic_param_py")
    server = Server(drConfig, callback)
    rospy.spin()
