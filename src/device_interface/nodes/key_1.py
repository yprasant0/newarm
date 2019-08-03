#!/usr/bin/env python
import sys, select, termios, tty
import rospy
import geometry_msgs.msg 
from geometry_msgs.msg import Pose


def publisher():
	rospy.init_node("arm_val",anonymous=True)
	pub = rospy.Publisher('pubDeviceOut', Pose,queue_size = 1)
	rate = rospy.Rate(1)
	while not rospy.is_shutdown():
	    pub2 = key()
	    pub.publish(pub2)	
	    rate.sleep()
	

def getKey():
	global key1
	tty.setraw(sys.stdin.fileno())
	print "1"
	select.select([sys.stdin], [], [], 0)
	key1 = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	print key1
	return key1

def key():
	global x,key1
	pub1 = Pose()
	print 'enter values'
	x = getKey()
	if x == 'x':
	   pub1.position.x +=  1
	elif x == 'y':
	   pub1.position.y +=  1
	elif x == 'y':
	   pub1.position.y +=  1
	elif key == '\x03':
           break			
	else :
	   pub1.position.x = 0 
	   pub1.position.y = 0
	   pub1 = Pose()
	return pub1  
	

if __name__=='__main__':
	try:	
	   settings = termios.tcgetattr(sys.stdin)
	   termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	   publisher()
           rospy.spin()
	except rospy.ROSInterruptException:
           pass


		
 		

