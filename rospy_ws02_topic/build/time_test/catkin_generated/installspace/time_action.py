#!/usr/bin/env python3

import rospy

rospy.init_node("time_action")

rightnow = rospy.Time.now()
rospy.loginfo("当前时间为：%.2f",rightnow.to_sec())

# 自定义时间
diy_time01 = rospy.Time(12345,12)
diy_time02 = rospy.Time(12345.12)
rospy.loginfo(diy_time01.to_sec())
rospy.loginfo(diy_time02.to_sec())
rospy.loginfo(diy_time02 - diy_time01)

# output:
# 12345.000000012
# 12345.12

# 设置时间
diy_time03 = rospy.Time.from_sec(54321.12)
diy_time04 = rospy.Time.from_seconds(54321.12)

# 持续时间
durTime = rospy.Duration(2)
rospy.loginfo("start")
rospy.sleep(durTime)
rospy.loginfo("end")

# 时间运算
durTime01 = rospy.Duration(10)
durTime02 = rospy.Duration(20)
beforeTime = rightnow - durTime01
afterTime = rightnow + durTime02
durDura = durTime01 + durTime02
rightnow02 = rospy.Time.now()
durDura02 = rightnow02.to_sec() - rightnow.to_sec()
rospy.loginfo(durDura.to_sec())
rospy.loginfo(durDura02)

if __name__ == "__main__":
    # 定时器
    def doTime(event):
        rospy.loginfo("00000")
        rospy.loginfo("当前时间为：%s",str(event.current_real))

    rospy.Timer(rospy.Duration(2),doTime)
    rospy.spin()