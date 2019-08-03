#!/usr/bin/env python
import roslib
import rospy
import math
import tf
import geometry_msgs.msg
from geometry_msgs.msg import Twist

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
	pub = rospy.Publisher('custom_joy', Twist,queue_size=50)
	rospy.init_node('arm_val')
			
	j1 = 0
	j2 = 0
	j3 = 0
	j4 = 0
	j5 = 0
	j6 = 0
	status = 0
	try:
		print msg
		while(1):
			key = getKey()
			if key == 'a' or key == 's' or key == 'd' or key == 'z' or key == 'x' or key == 'c':
						
				while not key != 'a':
					j1 =  j1 + 1 
					break
				while not key != 's':
		   			j2 =  j2 + 1
					break
				while not key != 'd':
					j3 =  j3 + 1
					break
				while not key != 'z':
					j1 =  j1 - 1
					break
				while not key != 'x':
					j2 =  j2 - 1
					break
				while not key != 'c':
					j3 =  j3 - 1
					break
				while not key != 'h':
					j4 = j4 + 1
					break
				
				"""while key != 'x' or key != 'y' or key != 'z':
					x1 = 0
					y1 = 0
			    		z1 = 0
					break"""
			
			else:
			

		    		if(key == '\x03'):
					break
			pub1 = Twist()
			pub1.linear.x = j1
			pub1.linear.y = j2
			pub1.linear.z = j3
			pub.publish(pub1)
			
	except:
		print e
	finally:
		pub1 = Twist()
		pub1.linear.x = 0 
		pub1.linear.y = 0
		pub1.linear.z = 0
		pub.publish(pub1)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
			   		
		     	 	
			
