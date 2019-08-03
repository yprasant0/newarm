#!/usr/bin/env python

import rospy
import geometry_msgs.msg 
from geometry_msgs.msg import Pose


def publisher():
	rospy.init_node("arm_val",anonymous=True)
	print "1"
	pub = rospy.Publisher('pubDeviceOut', Pose,queue_size = 1)
	rate = rospy.Rate(1)
	print "2"
	while not rospy.is_shutdown():
	    pub2 = key()
	    pub.publish(pub2)	
	    rate.sleep()
	
def key():
	global x;
	print "4"
	pub1 = Pose()
	print 'enter values'
	x = raw_input()
	if x == 'z':
	   pub1.position.x +=  1
	   print "zzzz"
	elif x == 'y':
	   pub1.position.y +=  1
	else :
	   pub1.position.x = 0 
	   pub1.postion.y = 0
	   pub1 = Pose()
	return pub1  
	

if __name__=='__main__':
	try:	
	   publisher()
           rospy.spin()
	except rospy.ROSInterruptException:
           pass


		
 		

