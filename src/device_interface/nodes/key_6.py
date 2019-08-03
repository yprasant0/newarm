#!/usr/bin/env python
import rospy
import tf
import roslib
import math
from visualization_msgs.msg import InteractiveMarkerFeedback
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

import sys, select, termios, tty

msg = """
Enter keys :
"""

def getKey():
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key

def current_state_of_end_effector():
	global cx
	global cy
	"""cx = val.pose.position.x
	cy = val.pose.position.y
	cz = val.pose.position.z
	print cx"""
	
	
if __name__=="__main__":
    	settings = termios.tcgetattr(sys.stdin)
	pub = rospy.Publisher('pubDeviceOut', Pose,queue_size=50)
	rospy.init_node('arm_val',anonymous=True)
	rospy.Subscriber('/rviz_moveit_motion_planning_display/robot_interaction_interactive_marker_topic/feedback',InteractiveMarkerFeedback,current_state_of_end_effector)
	current_pose_e = current_state_of_end_effector()	
	x1 = 0
	y1 = 0
	z1 = 0
	status = 0
	try:
		print msg
		while(1):
			key = getKey()
			if key == 'a' or key == 's' or key == 'd' or key == 'z' or key == 'x' or key == 'c':
						
				while not key != 'a':
					x1 =  x1 + 1 
					break
				while not key != 's':
		   			y1 =  y1 + 1
					break
				while not key != 'd':
					z1 =  z1 + 1
					break
				while not key != 'z':
					x1 =  x1 - 1
					break
				while not key != 'x':
					y1 =  y1 - 1
					break
				while not key != 'c':
					z1 =  z1 - 1
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
			
	except(tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
		print e
	finally:
		pub1 = Pose()
		pub1.position.x = 0 
		pub1.position.y = 0
		pub1.position.z = 0
		pub.publish(pub1)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
			   		
		     	 	
			
