#!/usr/bin/env python

import rospy
import std_msgs.msg
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path
from aerostack_msgs.srv import ActivateBehavior

def publishTrajectory():
  t=0
  pub = rospy.Publisher('/drone111/motion_reference/path', Path, queue_size=10)
  rospy.init_node('test', anonymous=True)
  msg = Path()
  msg.header.frame_id = "map"
  msg.header.stamp = rospy.Time.now()
  pose = PoseStamped()

  z_ref=6.0 #En principio no controlamos la coordenada z

  pose = PoseStamped()
  pose.pose.position.x=0.0
  pose.pose.position.y=0.0
  pose.pose.position.z=z_ref

  msg.poses.append(pose)

  pose = PoseStamped()
  pose.pose.position.x=0.0
  pose.pose.position.y=14.0
  pose.pose.position.z=z_ref

  msg.poses.append(pose)

  pose = PoseStamped()
  pose.pose.position.x=14.0
  pose.pose.position.y=14.0
  pose.pose.position.z=z_ref

  msg.poses.append(pose)

  pose = PoseStamped()
  pose.pose.position.x=14.0
  pose.pose.position.y=0.0
  pose.pose.position.z=z_ref

  msg.poses.append(pose)

  pose = PoseStamped()
  pose.pose.position.x=0.0
  pose.pose.position.y=0.0
  pose.pose.position.z=z_ref

  msg.poses.append(pose)

  
  print(msg)

  rospy.sleep(1)

  pub.publish(msg)



if __name__ == '__main__':
  try:
    #publishTrajectory()
    rospy.wait_for_service('/drone111/quadrotor_motion_with_pid_control/behavior_follow_path/activate_behavior')
    activate_behavior = rospy.ServiceProxy('/drone111/quadrotor_motion_with_pid_control/behavior_follow_path/activate_behavior', ActivateBehavior)
    response = activate_behavior('path: [ [47.904166588416466,-51.633381770207336,15], [39.06573926485502,-51.633381770207336,15], [30.22731194129357,-51.633381770207336,15], [21.388884617732124,-51.633381770207336,15], [12.550457294170673,-51.633381770207336,15], [3.712029970609226,-51.633381770207336,15] ]', 10000)
  except rospy.ROSInterruptException:
    pass
