#!/usr/bin/env python
import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from std_msgs.msg import String
from math import pi
from std_msgs.msg import String

j1 = 0
j2 = 0
j3 = 0
j4 = 0
j5 = 
j6

  ## First initialize moveit_commander and rospy.
print "============ Starting tutorial setup"
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_interface', anonymous=True)
robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()
group = moveit_commander.MoveGroupCommander("arm")
display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path', moveit_msgs.msg.DisplayTrajectory, queue_size=20)

  ## Wait for RVIZ to initialize. This sleep is ONLY to allow Rviz to come up.
print "============ Waiting for RVIZ..."
#rospy.sleep(10)
print "============ Starting up "
print "============ Reference frame: %s" % group.get_planning_frame()
print "============ End effector: %s" % group.get_end_effector_link()
print "============ Robot Groups:"
print robot.get_group_names()
print "============ Printing robot state"
print robot.get_current_state()
print "============"
#rospy.sleep(5)

def robot_move_group_interface(msg):
    global w
    global x
    global y
    global z

    w = msg.w
    x = msg.x
    y = msg.y
    z = msg.z
    robot_move()

def listener():
    sub=rospy.Subscriber('device_interface_subscriber', geometry_msgs.msg.Pose, robot_move_group_interface)
    rospy.spin()

def robot_move():
    global w
    global x
    global y
    global z
    global group
    group.clear_pose_targets()
    print "============ Generating plan 1"
    pose_target = geometry_msgs.msg.Pose()
    pose_target.orientation.w = 1.0
    pose_target.position.x = 0.3
    pose_target.position.y = -0.19
    pose_target.position.z = 0.86
    #pose_target.orientation.w = 0.7
    #pose_target.position.x = 0.8
    #pose_target.position.y = -0.3
    #pose_target.position.z = 1.2
    group.set_pose_target(pose_target)
    plan1 = group.plan()
    print "============ Waiting while RVIZ displays plan1..."
    display_trajectory = moveit_msgs.msg.DisplayTrajectory()
    display_trajectory.trajectory_start = robot.get_current_state()
    display_trajectory.trajectory.append(plan1)
    display_trajectory_publisher.publish(display_trajectory);
    #rospy.sleep(5)
    ## Moving to a pose goal
    ## ^^^^^^^^^^^^^^^^^^^^
    #group.go(wait=True)
    #group.execute(plan1)

  
if __name__=='__main__':
  try:
    #listener()
    robot_move()
  except rospy.ROSInterruptException:
    pass
  
   
               
