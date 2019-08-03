/*
 * Copyright (C) 2015, Lentin Joseph and Qbotics Labs Inc.

 * Email id : qboticslabs@gmail.com

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.


* This code will publish a integers from 0 to n with a delay of 100ms

 */

//roscpp Core header 
#include "ros/ros.h"
//Header of Int32 standard message
#include "std_msgs/Float64.h"
#include <iostream>
#include <cmath>
#include <math.h> 
using namespace std;
void expand(int);


int main(int argc, char **argv)

{
	    float num1;
    cout<<"Enter x: ";
    cin>>num1;
    float x = num1;
    
float num2;    
        cout<<"Enter y : ";
    cin>>num2;
    float y = num2;
    
 float number_count1;
 float number_count;   
 float l1, l2;
 l1 = 8;
 l2 = 10.3;
float p = pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2);
float q = sqrt(1-(pow((p/(2*l1*l2)),2)));
float theta2=atan2 (q,(p/(2*l1*l2)));
float k1=l1+(l2*(cos(theta2)));
float k2=l2*(sin(theta2));
float gaama = atan2 (k2,k1);

float theta1=(atan2 (y,x))-gaama;
//theta1 = theta1 -gaama;
      ROS_INFO("theta1= %f",theta1);
 ROS_INFO("theta2= %f",theta2);

 
    number_count1 = (theta1);//*(M_PI/180);
    number_count = (theta2);//*(M_PI/180);
     ROS_INFO("number_count= %f",number_count);
 ROS_INFO("number_count1= %f",number_count1);
	//Initializing ROS node with a name of demo_topic_publisher
	ros::init(argc, argv,"demo_topic_publisher");

	//Created a node handle object
	ros::NodeHandle node_obj1;
//ros::NodeHandle node_obj2;
//ros::NodeHandle node_obj3;
ros::NodeHandle node_obj4;
	//Created a publisher object
	ros::Publisher number_publisher1 = node_obj1.advertise<std_msgs::Float64>("/seven_dof_arm/joint4_position_controller/command",10);
//ros::Publisher number_publisher2 = node_obj2.advertise<std_msgs::Float64>("/seven_dof_arm/joint2_position_controller/command",10);
//ros::Publisher number_publisher3 = node_obj3.advertise<std_msgs::Float64>("toggle_led",10);
ros::Publisher number_publisher4 = node_obj4.advertise<std_msgs::Float64>("/seven_dof_arm/joint2_position_controller/command",10);

	//Created a rate object
	ros::Rate loop_rate(10);

	//Variable of the number initializing as zero
	
	

	//While loop for incrementing number and publishing to topic /numbers
	while (ros::ok())
	{
	
		//if(number_count <=2 && number_count1 <=2){
		//Created a Int32 message
		std_msgs::Float64 msg1;
		//std_msgs::Float64 msg2;
		//std_msgs::Float64 msg3;
		std_msgs::Float64 msg4;
		//Inserted data to message header
		msg1.data = number_count;
		//msg2.data = number_count1;
				//msg3.data = number_count; 
	msg4.data = number_count1;
		//Printing message data
		//ROS_INFO("msg1 = %f",msg1.data);
		//ROS_INFO("msg2 = %f",msg2.data);
		//ROS_INFO("msg3 = %f",msg3.data);
		//ROS_INFO("msg4 = %f",msg4.data);
		//Publishing the topic 
		number_publisher1.publish(msg1);
	//number_publisher2.publish(msg2);
		//number_publisher3.publish(msg3);
			number_publisher4.publish(msg4);
		//Spinning once for doing the  all operation once
		ros::spinOnce();

		//Sleeping for sometime
		loop_rate.sleep();

		//Incrementing the count
		//number_count = number_count -1.5 ;
		//number_count1 = number_count1 -  1.5;
	//}
}	return 0;
}


