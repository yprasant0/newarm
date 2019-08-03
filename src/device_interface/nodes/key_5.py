#!/usr/bin/env python
import rospy
import moveit_commander
import moveit_msgs.msg
import numpy as np
import time
import sys
import copy
from geometry_msgs.msg import Pose

import sys, select, termios, tty

msg = """
Enter keys :
"""

def getKey():
	global starttime 
	starttime = time.time()
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key


if __name__=="__main__":
    	settings = termios.tcgetattr(sys.stdin)
	moveit_commander.roscpp_initialize(sys.argv)
	rospy.init_node('arm_val',anonymous = True)
	robot1 = moveit_commander.RobotCommander()
	scene1 = moveit_commander.PlanningSceneInterface()
	group1 = moveit_commander.MoveGroupCommander("arm")
	current_pose = group1.get_current_pose().pose
	x2 = current_pose.position.x
	y2 = current_pose.position.y
	z2 = current_pose.position.z
	print 'x2='+str(x2)+'y2='+str(y2)+'z2='+str(z2)
	pub = rospy.Publisher('pubDeviceOut', Pose,queue_size=50)
	x1 = x2/0.02
	y1 = y2/0.02
	z1 = z2/0.02
	print 'x2='+str(x1)+'y2='+str(y1)+'z2='+str(z1)
	status = 0
	try:
		print msg
		while(1):
			key = getKey()
			if key == 'a' or key == 's' or key == 'd' or key == 'z' or key == 'x' or key == 'c':
						
				while not key != 'a':
					x1 =  x1 + 0.5 
					break
				while not key != 's':
		   			y1 =  y1 + 0.5
					break
				while not key != 'd':
					z1 =  z1 + 0.5
					break
				while not key != 'z':
					x1 =  x1 - 0.5
					break
				while not key != 'x':
					y1 =  y1 - 0.5
					break
				while not key != 'c':
					z1 =  z1 - 0.5
					break
				"""while key != 'x' or key != 'y' or key != 'z':
					x1 = 0
					y1 = 0
			    		z1 = 0
					break"""
			
			else:
			

		    		if(key == '\x03'):
					break
			pub1 = Pose()
			pub1.position.x = x1 
			pub1.position.y = y1
			pub1.position.z = z1
			pub.publish(pub1)
			rospy.spin()
			
	except:
		print e
	finally:
		pub1 = Pose()
		pub1.position.x = 0 
		pub1.position.y = 0
		pub1.position.z = 0
		pub.publish(pub1)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
			   		
		     	 	
			
