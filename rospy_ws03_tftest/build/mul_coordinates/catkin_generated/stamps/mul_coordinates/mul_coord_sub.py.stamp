#! /usr/bin/env python

import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped
from tf2_geometry_msgs.tf2_geometry_msgs import PointStamped

if __name__ == "__main__":
    rospy.init_node("coord_sub")
    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        try:
            tfs = buffer.lookup_transform("coord01","coord02",rospy.Time(0))
            rospy.loginfo("相对关系：")
            rospy.loginfo("父系坐标系：%s",tfs.header.frame_id)
            rospy.loginfo("子系坐标系：%s",tfs.child_frame_id)
            rospy.loginfo("相对坐标：(%.2f,%.2f,%.2f)",
                          tfs.transform.translation.x,
                          tfs.transform.translation.y,
                          tfs.transform.translation.z)
            
            point_source = PointStamped()
            point_source.header.frame_id = "coord01"
            point_source.header.stamp = rospy.Time.now()
            point_source.point.x = 1.0
            point_source.point.y = 1.0
            point_source.point.z = 1.0

            point_target = buffer.transform(point_source,"coord02",rospy.Duration(0.5))
            rospy.loginfo("point所属坐标系为:%s",point_source.header.frame_id)
            rospy.loginfo("point相对于coord02的坐标为:(%.2f,%.2f,%.2f)",
                          point_target.point.x,
                          point_target.point.y,
                          point_target.point.z
                          )

        except Exception as e:
            rospy.logerr("错误提示:%s",e)

        rate.sleep()