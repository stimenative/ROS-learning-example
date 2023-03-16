#!/usr/bin/env python3

import rospy
import tf2_ros
import tf.transformations
from geometry_msgs.msg import TransformStamped

if __name__ == "__main__":
    
    rospy.init_node("static_pub")
    
    # 创建静态广播对象
    broadcast = tf2_ros.StaticTransformBroadcaster()
    
    # 创建消息
    tfs = TransformStamped()

    tfs.header.frame_id = "base"    # 坐标ID
    tfs.header.stamp = rospy.Time.now() # 时间戳
    tfs.header.seq = 101    # 序列号

    tfs.child_frame_id = "radar"    # 子坐标ID
    
    # 坐标偏移量
    tfs.transform.translation.x = 0.2
    tfs.transform.translation.y = 0.0
    tfs.transform.translation.z = 0.5

    # 四元数
    qtn = tf.transformations.quaternion_from_euler(0,0,0)
    tfs.transform.rotation.x = qtn[0]
    tfs.transform.rotation.y = qtn[1]
    tfs.transform.rotation.z = qtn[2]
    tfs.transform.rotation.w = qtn[3]

    broadcast.sendTransform(tfs)
    rospy.spin()
