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
import numpy as np
import time
from visualization_msgs.msg import Marker
from visualization_msgs.msg import MarkerArray
## END_SUB_TUTORIAL

from std_msgs.msg import String

w = 0.0
x = 0.0
y = 0.0
z = 0.0

'''
def cart2sph(x, y, z):
    hxy = np.hypot(x, y)
    r = np.hypot(hxy, z)
    el = np.arctan2(z, hxy)
    az = np.arctan2(y, x)
    return az, el, r

def sph2cart(az, el, r):
    rcos_theta = r * np.cos(el)
    x = rcos_theta * np.cos(az)
    y = rcos_theta * np.sin(az)
    z = r * np.sin(el)
    return x, y, z'''

def cart2sph(x,y,z):
    azimuth = np.arctan2(y,x)
    elevation = np.arctan2(z,np.sqrt(x**2 + y**2))
    r = np.sqrt(x**2 + y**2 + z**2)
    return azimuth, elevation, r

def sph2cart(azimuth,elevation,r):
    x = r * np.cos(elevation) * np.cos(azimuth)
    y = r * np.cos(elevation) * np.sin(azimuth)
    z = r * np.sin(elevation)
    return x, y, z

def constrain(val, min_val, max_val):
    return min(max_val, max(min_val, val))

def map(val, fromMin, fromMax, toMin, toMax):
    norm = (val - fromMin)/(fromMax - fromMin)
    mapped = norm * (toMax - toMin) + toMin
    return mapped


def robot_move_group_interface(msg):
    global starttime 
    starttime = time.time()    
    global w
    global x
    global y
    global z

    zoffset = 0.18
    xoffset = -0.0
    yoffset = 0.0
    minlim = 0.05
    maxlim = 0.45
    global zoffset2
    zoffset2 = 0.0

    z = msg.position.z
    #z = constrain(z, 0.1, 1)+ zoffset
    y = msg.position.y
    x = msg.position.x

    #z = constrain(z, 0, 309)
    #z = map(z,0,309,0,0.48)
    #x = constrain(x, 0, 309)
    #x = map(x, 0, 309, 0, 0.48)
    #y = constrain(y, 0, 309)
    #y = map(y,0,309,0,0.48)

    z = msg.position.z * 0.02
    #z = constrain(z, 0.1, 1)+ zoffset
    y = msg.position.y * 0.02
    x = msg.position.x * 0.02 #+ xoffset'''


    mag = (x**2 + y**2 + (z)**2) ** 0.5
    print x, y, z, mag
    if mag < maxlim and mag > minlim:
        global x, y, z
        print x, y, z
        robot_move()
    elif mag < minlim:
        global x, y, z
        (az, el, r) = cart2sph(x, y, z)
        r = minlim
        (x, y, z) = sph2cart(az, el, r)
        print x, y, z, r
        z = z + zoffset
        robot_move()
    elif mag > maxlim:
        global x, y, z
        (az, el, r) = cart2sph(x, y, z)
        r = maxlim
        (x, y, z) = sph2cart(az, el, r)
        print x, y, z, r
        z = z + zoffset
        robot_move()

def listener():
    sub=rospy.Subscriber('pubDeviceOut', geometry_msgs.msg.Pose, robot_move_group_interface, queue_size=1)
    rospy.spin()

def robot_move():
    markerArray = MarkerArray()
    marker = Marker()
    global count
    count = 0
    MARKERS_MAX = 100
    global zoffset2
    global group
    global x
    global y
    global z
    print x, y, z
    marker.header.frame_id = "/l6"
    marker.type = marker.SPHERE
    marker.action = marker.ADD
    marker.scale.x = 0.05
    marker.scale.y = 0.05
    marker.scale.z = 0.05
    marker.color.a = 1.0
    marker.color.r = 1.0
    marker.color.g = 1.0
    marker.color.b = 0.0
    marker.pose.orientation.w = 1.0
    marker.pose.position.x = x
    marker.pose.position.y = y
    marker.pose.position.z = z
    # We add the new marker to the MarkerArray, removing the oldest
    # marker from it when necessary
    if(count > MARKERS_MAX):
        markerArray.markers.pop(0)
    markerArray.markers.append(marker)
    # Renumber the marker IDs
    id = 0
    for m in markerArray.markers:
        m.id = id
        id += 1
    # Publish the MarkerArray
    publisher.publish(markerArray)
    count += 1
    pose_target = geometry_msgs.msg.Pose()
    pose_target = group.get_current_pose().pose
    waypoints = []
    pose_target.orientation.w = 1
    pose_target.position.x = x
    waypoints.append(copy.deepcopy(pose_target))
    pose_target.position.y = y
    waypoints.append(copy.deepcopy(pose_target))
    pose_target.position.z = z
    waypoints.append(copy.deepcopy(pose_target))
    #group.set_pose_target(pose_target)
    #group.set_joint_value_target(pose_target, True)
    #plan = group.plan()
    (plan, fraction) = group.compute_cartesian_path(waypoints, 0.005, 0.0)
    print "response time"
    global starttime    
    print starttime - time.time()
    print "============ Viz plan ==================="
    group.execute(plan)
    #group.go(wait=True)
    #rospy.sleep(1)



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
print "=================================="
#group.set_planner_id("RRTConnectkConfigDefault")
#group.set_planning_time(20)
  #rospy.sleep(5)

if __name__=='__main__':
  publisher = rospy.Publisher('visualization_marker_array', MarkerArray,queue_size = 1)
  try:

    listener()
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
