#!/usr/bin/env python3

import rospy

if __name__ == "__main__":
    rospy.init_node("add_para")

    # 设置参数
    rospy.set_param("para01_int",10)
    rospy.set_param("para02_double",2.56)
    rospy.set_param("para03_bool",True)
    rospy.set_param("para04_string","hello")
    rospy.set_param("para05_list",["a","b",3])
    rospy.set_param("para06_dict",{"name":"gwq","age":24})

    # 修改参数
    rospy.set_param("para02_double",4.62)

