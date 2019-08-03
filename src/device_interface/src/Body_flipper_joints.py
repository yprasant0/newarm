#!/usr/bin/env python
import copy
import sys
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
import std_msgs.msg
from std_msgs.msg import String
from geometry_msgs.msg import Twist

def listener():
	 sub=rospy.Subscriber('BODY', geometry_msgs.msg.Twist, robot_move_group_interface, queue_size=1)
	 rospy.spin()

def robot_move_group_interface(msg):
	global j1
	global j2
	global j3
	global j4
	j1 = msg.linear.x
	j2 = msg.linear.y
	j3 = msg.linear.z
	j4 = msg.angular.x
	robot_move()	


def robot_move():
	global j1
	global j2
	global j3
	global j4	
	group.clear_pose_targets()
  	group_variable_values = group.get_current_joint_values()
  	print "============ Joint values: ", group_variable_values
  	group_variable_values[0] = j1
 	group_variable_values[1] = j2
  	group_variable_values[2] = j3
  	group_variable_values[3] = j4
  	group.go(group_variable_values,wait=True)
	group.stop()



moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface_tutorial',
                  anonymous=True)
robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()
group = moveit_commander.MoveGroupCommander("flipper")
display_trajectory_publisher = rospy.Publisher(
                                      '/move_group/display_planned_path',
                                      moveit_msgs.msg.DisplayTrajectory)

print "============ Waiting for RVIZ..."
print "============ Starting tutorial "
print "============ Reference frame: %s" % group.get_planning_frame()
print "============ Robot Groups:"
print robot.get_group_names()
print "============ Printing robot state"
print robot.get_current_state()
print "============"
print "============ Waiting while RVIZ displays plan2..."
rospy.sleep(5)



if __name__=='__main__':
  try:
    listener()
  except rospy.ROSInterruptException:
    pass


