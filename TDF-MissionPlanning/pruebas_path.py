#!/usr/bin/env python

import rospy
import tf
import std_msgs.msg
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path

def publishTrajectory():
  t=0
  pub = rospy.Publisher('/drone111/motion_reference/path', Path, queue_size=10)
  rospy.init_node('test', anonymous=True)
  #rate = rospy.Rate(10) #10 Hz
  msg = Path()
  msg.header.frame_id = "map"
  msg.header.stamp = rospy.Time.now()
  pose1 = PoseStamped()
  pose2 = PoseStamped()
  pose3 = PoseStamped()

  z_ref=6.0 #En principio no controlamos la coordenada z

  
  pose1.pose.position.x=6.0
  pose1.pose.position.y=6.0
  pose1.pose.position.z=z_ref

  msg.poses.append(pose1)

  pose2.pose.position.x=1.0
  pose2.pose.position.y=-1.0
  pose2.pose.position.z=z_ref

  msg.poses.append(pose2)

  pose3.pose.position.x=1.0
  pose3.pose.position.y=-1.0
  pose3.pose.position.z=z_ref

  msg.poses.append(pose3)

  
  print(msg)

  rospy.sleep(1)

  pub.publish(msg)



if __name__ == '__main__':
  try:
    publishTrajectory()
  except rospy.ROSInterruptException:
    pass
