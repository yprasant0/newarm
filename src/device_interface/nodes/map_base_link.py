#!/usr/bin/env python  
import roslib
import rospy
import math
import tf
import geometry_msgs.msg
from geometry_msgs.msg import Pose


if __name__ == '__main__':
    rospy.init_node('required_robot_coordinates')

    listener = tf.TransformListener()


    img_coordinates = rospy.Publisher('detected_image_coordinates', geometry_msgs.msg.Pose,queue_size=100)
    

    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform('/base_link', '/l6', rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            rospy.loginfo(rospy.get_name()+"  can not find transform")
	    continue
        
	cmd = geometry_msgs.msg.Pose()	
	cmd.position.x = trans[0]
	cmd.position.y = trans[1]
	cmd.position.z = trans[2]
	rospy.loginfo(rospy.get_name()+"  %d %d %d", cmd.position.x, cmd.position.y, cmd.position.z)
        img_coordinates.publish(cmd)
	

        rate.sleep()
