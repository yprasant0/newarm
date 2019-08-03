#include <Wire.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#include <ros/time.h>
#include <SoftwareSerial.h>

ros::NodeHandle nh;
//#define potPin A0
#define j2_min 450
#define j2_max 3445
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);  //rx tx

byte header = 0xAA;
byte deviceAddress = 0x04;
byte dataH = 0x00;    //0x40 + last 5 bits
byte dataL = 0x00;    //first 7 bits

//Range conversion
int inputRaw = 0;
int inputScaled = 0;
int inputRange[2] = {0, 1023};
int outputRange[2] = {0, 4095};

int in2 = 2015; 
//Serial Buffer
const int buffLen = 4;
byte buff[buffLen] = {header, deviceAddress, dataH, dataL};

std_msgs::Float64 j2;
void input2( const std_msgs::Float64 & cmd_msg2){
   j2.data = cmd_msg2.data;
   float deg2 = j2.data * 180 / M_PI;
   deg2 = deg2 * -14.5 + in2;
   deg2 = constrain(deg2, j2_min, j2_max);
   Move(deg2, deviceAddress);   
}

ros::Subscriber<std_msgs::Float64> sub2("joint_1", &input2);

void Move(int x, byte address) {
  word target = x; //only pass this ints, i tried doing math in this and the remainder error screwed something up
  byte deviceAddress = address;
  mySerial.write(0xAA); //tells the controller we're starting to send it commands
  mySerial.write(deviceAddress);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
  mySerial.write(0x40 + (target & 0x1F)); //first half of the target, see the pololu jrk manual for more specifics
  mySerial.write((target >> 5) & 0x7F);   //second half of the target, " " " 

  Serial.print(0xAA,HEX); //tells the controller we're starting to send it commands
  Serial.print(deviceAddress,HEX);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
  Serial.print(0x40 + (target & 0x1F),HEX); //first half of the target, see the pololu jrk manual for more specifics
  Serial.print((target >> 5) & 0x7F,HEX);   //second half of the target, " " " 
  Serial.println();
}  

void setup() 
{
  Serial.begin(57600);
  mySerial.begin(57600);
  //pinMode(potPin, INPUT);
  Move(in2, deviceAddress);
  nh.initNode();
  nh.subscribe(sub2);
}

void loop() 
{
  //inputRaw = analogRead(A0);
  //inputScaled = map(inputRaw, inputRange[0], inputRange[1], outputRange[0], outputRange[1]);
  //Move(inputScaled);
  nh.spinOnce();
  delay(10);
}
