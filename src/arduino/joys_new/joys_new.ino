#include <Wire.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point32.h>
#include <ros/time.h>
ros::NodeHandle  nh;


geometry_msgs::Twist joy_msg1;
ros::Publisher pub_joy1("ARM", &joy_msg1);
geometry_msgs::Point32 joy_msg2;
ros::Publisher pub_joy2("GRIPPER", &joy_msg2);
geometry_msgs::Twist joy_msg3;
ros::Publisher pub_joy3("cmd_vel", &joy_msg3);
geometry_msgs::Point32 joy_msg4;
ros::Publisher pub_joy4("joystick4", &joy_msg4);
geometry_msgs::Point32 joy_msg5;
ros::Publisher pub_joy5("joystick5", &joy_msg5);

void setup()
{
   Wire.begin();  
  
  nh.initNode();
  nh.advertise(pub_joy1);
  nh.advertise(pub_joy2);
  nh.advertise(pub_joy3);
  nh.advertise(pub_joy4);
  nh.advertise(pub_joy5);
}
long publisher_timer;
float a1 = 0;
float b1 = 0;
float c1 = 0;
float a2 = 0;
float b2 = 0;
float c2 = 0;
float a3 = 0;
float b3 = 0;
float c3 = 0;
void loop() 
{

float x1 = analogRead(A1);
float y1 = analogRead(A0);
float z1 = analogRead(A2);
//int w1 = analogRead(A13);
float x2 = analogRead(A4);
float y2 = analogRead(A3);
float z2 = analogRead(A5);
//int w2 = analogRead(A14);
int x3 = analogRead(A7);
int y3 = analogRead(A6);
//int z3 = analogRead(A8);
//int w3 = analogRead(A15);
//int x4 = analogRead(A10);
//int y4 = analogRead(A9);
//int x5 = analogRead(A12);
//int y5 = analogRead(A11);

if((analogRead(A1)>=580)&&(analogRead(A1)<980))
{
 if(a1<=3.14){
  a1 = a1 + 0.001;
 } 
 else{
  a1 = 3.10;
 }
}
else if((analogRead(A1)>=980)&&(analogRead(A1)<=1023))
{
 if(a1<=3.14){
  a1 = a1 + 0.01;
 } 
 else{
  a1 = 3.10;
 }
}
else if((analogRead(A1)>=90)&&(analogRead(A1)<=460))
{
  if(a1>=-3.14){
    a1 = a1 - 0.001;
  }
  else{
  a1 = -3.10;
 }
}
if((analogRead(A1)>=0)&&(analogRead(A1)<90))
{
 if(a1>=-3.14){
  a1 = a1 - 0.01;
 } 
 else{
  a1 = -3.10;
 }
}
if((analogRead(A0)>=580)&&(analogRead(A0)<980))
{
 if(b1<=0.78){
  b1 = b1 + 0.001;
 } 
 else{
  b1 = 0.75;
 }
}
else if((analogRead(A0)>=980)&&(analogRead(A0)<=1023))
{
 if(b1<=0.78){
  b1 = b1 + 0.01;
 } 
 else{
  b1 = 0.75;
 }
}
else if((analogRead(A0)>=90)&&(analogRead(A0)<=460))
{
  if(b1>=-0.78){
    b1 = b1 - 0.001;
  }
  else{
  b1 = -0.75;
 }
}
if((analogRead(A0)>=0)&&(analogRead(A0)<90))
{
 if(b1>=-0.78){
  b1 = b1 - 0.01;
 } 
 else{
  b1 = -0.75;
 }
}
if((analogRead(A2)>=580)&&(analogRead(A2)<980))
{
 if(c1<=1.30){
  c1 = c1 + 0.001;
 } 
 else{
  c1 = 1.25;
 }
}
else if((analogRead(A2)>=980)&&(analogRead(A2)<=1023))
{
 if(c1<=1.30){
  c1 = c1 + 0.01;
 } 
 else{
  c1 = 1.25;
 }
}
else if((analogRead(A2)>=90)&&(analogRead(A2)<=460))
{
  if(c1>=-1.30){
    c1 = c1 - 0.001;
  }
  else{
  c1 = -1.25;
 }
}
if((analogRead(A2)>=0)&&(analogRead(A2)<90))
{
 if(c1>=-1.30){
  c1 = c1 - 0.01;
 } 
 else{
  c1 = -1.25;
 }
}
if((analogRead(A4)>=580)&&(analogRead(A4)<980))
{
 if(a2<=1.57){
  a2 = a2 + 0.001;
 } 
 else{
  a2 = 1.55;
 }
}
else if((analogRead(A4)>=980)&&(analogRead(A4)<=1023))
{
 if(a2<=1.57){
  a2 = a2 + 0.01;
 } 
 else{
  a2 = 1.55;
 }
}
else if((analogRead(A4)>=90)&&(analogRead(A4)<=460))
{
  if(a2>=-1.57){
    a2 = a2 - 0.001;
  }
  else{
  a2 = -1.55;
 }
}
if((analogRead(A4)>=0)&&(analogRead(A4)<90))
{
 if(a2>=-1.57){
  a2 = a2 - 0.01;
 } 
 else{
  a2 = -1.55;
 }
}
if((analogRead(A3)>=580)&&(analogRead(A3)<980))
{
 if(b2<=1.57){
  b2 = b2 + 0.001;
 } 
 else{
  b2 = 1.55;
 }
}
else if((analogRead(A3)>=980)&&(analogRead(A3)<=1023))
{
 if(b2<=1.57){
  b2 = b2 + 0.01;
 } 
 else{
  b2 = 1.55;
 }
}
else if((analogRead(A3)>=90)&&(analogRead(A3)<=460))
{
  if(b2>=-1.57){
    b2 = b2 - 0.001;
  }
  else{
  b2 = -1.55;
 }
}
if((analogRead(A3)>=0)&&(analogRead(A3)<90))
{
 if(b2>=-1.57){
  b2 = b2 - 0.01;
 } 
 else{
  b2 = -1.55;
 }
}
if((analogRead(A5)>=580)&&(analogRead(A5)<980))
{
 if(c2<=1.57){
  c2 = c2 + 0.001;
 } 
 else{
  c2 = 1.55;
 }
}
else if((analogRead(A5)>=980)&&(analogRead(A5)<=1023))
{
 if(c2<=1.57){
  c2 = c2 + 0.01;
 } 
 else{
  c2 = 1.55;
 }
}
else if((analogRead(A5)>=90)&&(analogRead(A5)<=460))
{
  if(c2>=-1.57){
    c2 = c2 - 0.001;
  }
  else{
  c2 = -1.55;
 }
}
if((analogRead(A5)>=0)&&(analogRead(A5)<90))
{
 if(c2>=-1.57){
  c2 = c2 - 0.01;
 } 
 else{
  c2 = -1.55;
 }
}

if((analogRead(A7)>=580)&&(analogRead(A7)<980))
{
 if(a3<=0.5){
  a3 = a3 + 0.001;
 } 
 else{
  a3 = 0.4;
 }
}
else if((analogRead(A7)>=980)&&(analogRead(A7)<=1023))
{
 if(a3<=0.5){
  a3 = a3 + 0.01;
 } 
 else{
  a3 = 0.4;
 }
}
else if((analogRead(A7)>=90)&&(analogRead(A7)<=460))
{
  if(a3>=-0.5){
    a3 = a3 - 0.001;
  }
  else{
  a3 = -0.4;
 }
}
if((analogRead(A7)>=0)&&(analogRead(A7)<90))
{
 if(a3>=-0.5){
  a3 = a3 - 0.01;
 } 
 else{
  a3 = -0.4;
 }
}

if((analogRead(A6)>=580)&&(analogRead(A6)<980))
{
 if(b3<=0.5){
  b3 = b3 + 0.001;
 } 
 else{
  b3 = 0.4;
 }
}
else if((analogRead(A6)>=980)&&(analogRead(A6)<=1023))
{
 if(b3<=0.5){
  b3 = b3 + 0.01;
 } 
 else{
  b3 = 0.4;
 }
}
else if((analogRead(A6)>=90)&&(analogRead(A6)<=460))
{
  if(b3>=-0.5){
    b3 = b3 - 0.001;
  }
  else{
  b3 = -0.4;
 }
}
if((analogRead(A6)>=0)&&(analogRead(A6)<90))
{
 if(b3>=-0.5){
  b3 = b3 - 0.01;
 } 
 else{
  b3 = -0.4;
 }
}

joy_msg1.linear.x = a1;
joy_msg1.linear.y = b1;
joy_msg1.linear.z = c1;
joy_msg1.angular.x = a2;
joy_msg1.angular.y = b2;
joy_msg1.angular.z = c2;
//joy_msg2.x= w1;
//joy_msg2.y = w2;
joy_msg3.linear.x = a3;
joy_msg3.linear.y = b3;
//joy_msg3.z = z3;
//joy_msg3.w = w3;
//joy_msg4.x = x4;
//joy_msg4.y = y4;
//joy_msg5.x = x5;
//joy_msg5.y = y5;
pub_joy1.publish(&joy_msg1);
pub_joy2.publish(&joy_msg2);
pub_joy3.publish(&joy_msg3);
pub_joy4.publish(&joy_msg4);
pub_joy5.publish(&joy_msg5);
nh.spinOnce();
}
