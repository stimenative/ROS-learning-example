#!/usr/bin/env python3

import rospy

if __name__ == "__main__":
    rospy.init_node("get_para")

    # 获取参数 rospy.get_param(name,default)
    para01_intValue = rospy.get_param("para01_int")
    para01_intValue2 = rospy.get_param("para01_int2",100)
    para02_doubleValue = rospy.get_param("para02_double")
    para03_boolValue = rospy.get_param("para03_bool")
    para05_list = rospy.get_param("para05_list")
    para06_dict = rospy.get_param("para06_dict")

    rospy.loginfo("获取的数据为：%d,%d,%.3f,%d",
                  para01_intValue,
                  para01_intValue2,
                  para02_doubleValue,
                  para03_boolValue)
    rospy.loginfo("iist data:")
    for elem in para05_list:
        rospy.loginfo(elem)

    # 类似方法 rospy.get_param_cached()
    int_cach = rospy.get_param_cached("para01_int")
    name = rospy.get_param_names()
    print(name)

    # 判断是否存在参数 rospy.has_param()
    flag = rospy.has_param("para03_bool")
    if flag:
        print("exict")
    else:
        print("no exict")

    # 搜索参数，若存在返回参数名，若不存在返回None rospy.search_param()
    key = rospy.search_param("para02_int")
    print(key)

 