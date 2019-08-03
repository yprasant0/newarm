#!/usr/bin/env python
import rospy

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
	x1 = 0
	y1 = 0
	z1 = 0
	status = 0
	try:
		print msg
		while(1):
			key = getKey()
			if key == 'x' or key == 'y' or key == 'z':
						
				while not key != 'x':
					x1 =  x1 + 1 
					break
				while not key != 'y':
		   			y1 =  y1 + 1
					break
				while not key != 'z':
					z1 =  z1 + 1
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
		pub.publish(pub1)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
			   		
		     	 	
			
