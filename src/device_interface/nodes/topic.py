#!/usr/bin/env python
import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
import numpy as np
import time
from math import sin,cos,degrees
from std_msgs.msg import String

global r	
global az
global el


def cyl2cart(r,az,el):
   x = r * cos(az)
   y = r * sin(az)
   z = el
   print x,y,z
   return x,y,z

def constrain(val, min_val, max_val):
    return min(max_val, max(min_val, val))

def robot_move_group_interface(msg):
    global x
    global y
    global z
    global w
    r = msg.position.x/120
    az = msg.position.y/150
    el = msg.position.z/150
    w = msg.orientation.x/155
    (x,y,z) = cyl2cart(r,az,el);	
    x = constrain(x, 0.3, 1.5)
    y = constrain(y, -1.3, 1.30)
    z = constrain(z, -1.3, 1.30)
    print "s"
    print x, y, z
    robot_move()

def listener():
    sub=rospy.Subscriber('pubDeviceOut', geometry_msgs.msg.Pose, robot_move_group_interface, queue_size=1)
    rospy.spin()

def robot_move():
    global group

    print "============ Generating plan 1"
    pose_target = geometry_msgs.msg.Pose()
    pose_target.orientation.w = 1
    pose_target.position.x = x 
    pose_target.position.y = y  
    pose_target.position.z = z 
    group.set_pose_target(pose_target)
    plan1 = group.plan()
    print "============ Waiting while RVIZ displays plan1..."
    #print robot.get_current_state()
    print group.get_current_pose()
    #rospy.sleep(3)
    ## Moving to a pose goal
    ## ^^^^^^^^^^^^^^^^^^^^
    group.go(wait=True)
    #group.execute(plan1)



  ## First initialize moveit_commander and rospy.
print "============ Starting tutorial setup"
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_interface', anonymous=True)
robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()
group = moveit_commander.MoveGroupCommander("arm")
display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path', moveit_msgs.msg.DisplayTrajectory, queue_size=0)

  ## Wait for RVIZ to initialize. This sleep is ONLY to allow Rviz to come up.
print "============ Waiting for RVIZ..."
#rospy.sleep(10)
print "============ Starting up "
print "============ Reference frame: %s" % group.get_planning_frame()
print "============ End effector: %s" % group.get_end_effector_link()
print "============ Robot Groups:"
print robot.get_group_names()
print "============ Printing robot state"
print group.get_current_pose()
print "============"
  #rospy.sleep(5)
  
if __name__=='__main__':
  try:
    
    listener()
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
  
   
               
