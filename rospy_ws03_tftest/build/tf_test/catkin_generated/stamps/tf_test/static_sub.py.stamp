#! /usr/bin/env python

import rospy
import tf2_ros

from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ == "__main__":
    rospy.init_node("static_sub")

    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        point_source = tf2_geometry_msgs.PointStamped()
        point_source.header.frame_id = "radar"
        point_source.header.stamp = rospy.Time.now()
        point_source.point.x = 2.0
        point_source.point.y = 3.0
        point_source.point.z = 5.0

        try:    # 有概率存在时间错位
            point_target = buffer.transform(point_source,"base")
            rospy.loginfo("result: %.2f,%.2f,%.2f",point_target.point.x,point_target.point.y,point_target.point.z)
        except Exception as e:
            rospy.logwarn("error:%s",e)

        rate.sleep()