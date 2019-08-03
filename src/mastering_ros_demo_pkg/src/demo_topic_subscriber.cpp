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


	* This code will subscriber integer values from demo_topic_publisher

	*/


	#include <ros/ros.h>
	#include <sensor_msgs/JointState.h>
  #include <std_msgs/Float64.h>
  #include <std_msgs/String.h>
  #include <iostream>
std_msgs::Float64 msg0,msg1,msg2,msg3,msg4,msg5;
std_msgs::String name;
	void callback(const sensor_msgs::JointState &msg)
	{
    name.data = msg.name[0];
  msg0.data =  msg.position[0]; //approx working -6 8.43182* 
  msg1.data =  msg.position[1]; //5.50 -4.3162*
  msg2.data =  msg.position[2]; //2.5 -3.2175* −0.091737
  msg3.data =  msg.position[3]; //-1.5 -4.7301*
  msg4.data =  msg.position[4]; //5.80 && 5.1030*
  msg5.data =  msg.position[5];  //approx working -4 */ // -3.1354*
  
/* 

*/


    //ROS_INFO("adjglaioueg:[%f]", msg1.data);

	
   ROS_INFO("Received joint0:[%f]", msg.position[0]);
   ROS_INFO("Received joint1:[%f]", msg.position[1]);
   ROS_INFO("Received joint2:[%f]", msg.position[2]);
   ROS_INFO("Received joint3:[%f]", msg.position[3]);
   ROS_INFO("Received joint4:[%f]", msg.position[4]);
   ROS_INFO("Received joint5:[%f]", msg.position[5]);
   

	 
	} 
	
	
	int main(int argc, char** argv) {
	ros::init(argc, argv, "move_joint");
  ros::NodeHandle node_obj;
  ros::Subscriber joint_sub = node_obj.subscribe("joint_states", 10, callback);
  ros::NodeHandle node_obj0;
  ros::NodeHandle node_obj1;
  ros::NodeHandle node_obj2;
  ros::NodeHandle node_obj3;
  ros::NodeHandle node_obj4;
  ros::NodeHandle node_obj5;
  ros::NodeHandle node_ob;

  
  ros::Publisher number_publisher;
  ros::Publisher number_publisher0;
  ros::Publisher number_publisher1;
  ros::Publisher number_publisher2;
  ros::Publisher number_publisher3;
  ros::Publisher number_publisher4;
  ros::Publisher number_publisher5;
  
  number_publisher = node_ob.advertise<std_msgs::String>("joint_name",10);
  number_publisher0 = node_obj0.advertise<std_msgs::Float64>("joint_0",10);
  number_publisher1 = node_obj1.advertise<std_msgs::Float64>("joint_1",10);
  number_publisher2 = node_obj2.advertise<std_msgs::Float64>("joint_2",10);
  number_publisher3 = node_obj3.advertise<std_msgs::Float64>("joint_3",10);
  number_publisher4 = node_obj4.advertise<std_msgs::Float64>("joint_4",10);
  number_publisher5 = node_obj5.advertise<std_msgs::Float64>("joint_5",10);
  

  ros::Rate loop_rate(10);

while (ros::ok()){

  //ROS_INFO("name is = %s",name.data);
  number_publisher.publish(name);
  number_publisher0.publish(msg0);
  number_publisher1.publish(msg1);
  number_publisher2.publish(msg2);
  number_publisher3.publish(msg3);
  number_publisher4.publish(msg4);
  number_publisher5.publish(msg5);
  
  ros::spinOnce();

  loop_rate.sleep();

}return 0;
	}


