#!/usr/bin/env python
import roslib
import rospy
import math
import tf
import geometry_msgs.msg
from geometry_msgs.msg import Pose

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
	

if __name__=="__main__":
    	settings = termios.tcgetattr(sys.stdin)
	pub = rospy.Publisher('pubDeviceOut', Pose,queue_size=50)
	rospy.init_node('arm_val')
	listener = tf.TransformListener()
	while not rospy.is_shutdown():
        	try:
            		(trans,rot) = listener.lookupTransform('/base_link', '/l6', rospy.Time(0))
        	except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
	    		continue
        
			
		x1 = trans[0]
		y1 = trans[1]
		z1 = trans[2]
		break
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
				while not key != 'h':
					x3 = x3 + 1
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
			
	except:
		print e
	finally:
		pub1 = Pose()
		pub1.position.x = 0 
		pub1.position.y = 0
		pub1.position.z = 0
		pub1.orientation.x = 0
		pub.publish(pub1)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
			   		
		     	 	
			
