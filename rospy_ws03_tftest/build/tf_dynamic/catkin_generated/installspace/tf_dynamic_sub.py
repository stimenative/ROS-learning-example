#!/usr/bin/env python3

import rospy
import tf2_ros
from tf2_geometry_msgs.tf2_geometry_msgs import PointStamped

if __name__ == "__main__":
    rospy.init_node("dynamic_sub")
    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        point_source = PointStamped()
        point_source.header.frame_id = "turtle1"
        point_source.header.stamp = rospy.Time.now()
        
        # 相对于turtle的座标点
        point_source.point.x = 10 
        point_source.point.y = 10 
        point_source.point.z = 10 

        try:
            point_target = buffer.transform(point_source,"base",rospy.Duration(1))
            rospy.loginfo(
                "result: %.2f,%.2f,%.2f",
                point_target.point.x,
                point_target.point.y,
                point_target.point.z
            )
        except Exception as e:
            rospy.loginfo("err: %s",e)

        rate.sleep()