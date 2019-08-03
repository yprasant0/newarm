#!/usr/bin/env python

# Software License Agreement (BSD License)
#
# Copyright (c) 2013, SRI International
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of SRI International nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Author: Acorn Pooley

## BEGIN_SUB_TUTORIAL imports
##
## To use the python interface to move_group, import the moveit_commander
## module.  We also import rospy and some messages that we will use.
import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
## END_SUB_TUTORIAL

from std_msgs.msg import String

w = 0.0
x = 0.0
y = 0.0
x1 = 0.0
y1 = 0.0
z1 = 0.0
z = 0.0

def constrain(val, min_val, max_val):
    return min(max_val, max(min_val, val))

def robot_move_group_interface(msg):
    global x
    global y
    global z
    global x1
    global y1	
    global z1
    global w
    x = msg.position.x/155
    y = msg.position.y/150
    z = msg.position.z/150
    x1 = msg.orientation.x/155
    y1 = msg.orientation.y/155
    z1 = msg.orientation.z/150
    w = msg.orientation.w	
    x = constrain(x, 0.3, 1.5)
    y = constrain(y, -1.3, 1.30)
    z = constrain(z, -1.3, 1.30)
    print x, y, z
    robot_move()

def listener():
    sub=rospy.Subscriber('pubDeviceOut', geometry_msgs.msg.Pose, robot_move_group_interface, queue_size=1)
    rospy.spin()

def robot_move():
    global group

    print "============ Generating plan 1"
    pose_target = geometry_msgs.msg.Pose()
    pose_target.orientation.w = w
    pose_target.position.x = x 
    pose_target.position.y = y  
    pose_target.position.z = z 
    pose_target.orientation.x = x1
    pose_target.orientation.y = y1
    pose_target.orientation.z = z1
    pose_target.orientation.w = w
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
group = moveit_commander.MoveGroupCommander("arm_final")
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
  
   
               
