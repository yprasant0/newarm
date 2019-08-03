#include<ros.h>
#include<std_msgs/Float64.h>
#include <std_msgs/String.h>
#include<std_msgs/UInt32.h>

#define serialCount 20
#define step 10

#define r_1 42 // pin number for mega
#define r_2 43
#define r_3 30
#define r_4 31 

#define j1_min 175
#define j1_max 3365

#define j2_min 450
#define j2_max 3445

#define j3_min 3660
#define j3_max 1410

#define j4_min 4095
#define j4_max 200

#define j5_min 3425
#define j5_max 10

#define j6_min 60
#define j6_max 4050

//PINS FOR THE MUX
#define s1 3
#define s2 4
#define s3 5
#define en 6 


byte header = 0xAA;
byte deviceAddress [6] = {0x1, 0x02, 0x03, 0x04, 0x05, 0x06};
byte dataH = 0x00;    //0x40 + last 5 bits
byte dataL = 0x00;    //first 7 bits
byte feed1 = 0xA5;

//Range conversion
int input0Raw = 0;
int input0Scaled = 0;
int input1Raw = 0;
int input1Scaled = 0;
int inputRange[2] = {0, 1023};
int outputRange[2] = {0, 4095};

int in1 = 1770; 
int in2 = 2015; 
int in3 = 2095; 
int in4 = 2226;
int in5 = 1757;
int in6 = 2129;

//Serial Buffer
const int buffLen = 4;
byte buff[buffLen] = {header, deviceAddress, dataH, dataL};

ros :: NodeHandle nh ;
std_msgs::UInt32 str_msg1;
std_msgs::UInt32 str_msg2;
std_msgs::UInt32 str_msg3;
std_msgs::UInt32 str_msg4;
std_msgs::UInt32 str_msg5;
std_msgs::UInt32 str_msg6;

ros::Publisher chatter1("chatter1", &str_msg1);
ros::Publisher chatter2("chatter2", &str_msg2);
ros::Publisher chatter3("chatter3", &str_msg3);
ros::Publisher chatter4("chatter4", &str_msg4);
ros::Publisher chatter5("chatter5", &str_msg5);
ros::Publisher chatter6("chatter6", &str_msg6);

std_msgs::Float64 msg1,msg2,msg3, msg4, msg5, msg6;

word msgCb1 (const std_msgs :: Float64 & incoming_msg1)
{
  word data;
  msg1.data = incoming_msg1.data;
  float deg1 = msg1.data * 180 / M_PI;
  deg1 = deg1 * -14.5 + in1;
  deg1 = constrain(deg1, j1_min, j1_max);
  Move(deg1, deviceAddress[0]);
  data = feedBack(deviceAddress[0]);
  str_msg1.data = data;
  chatter1.publish( &str_msg1);
   
}

void msgCb2(const std_msgs :: Float64 & incoming_msg2)
{
  word data;
  msg2.data = incoming_msg2.data;
  float deg2 = msg2.data * 180 / M_PI;
  deg2 = deg2 * -14.22 + in2;
  deg2 = constrain(deg2, j2_min, j2_max);
  Move(deg2, deviceAddress[1]);
  data = feedBack(deviceAddress[1]);
  str_msg2.data = data;
  chatter2.publish( &str_msg2);
}

void msgCb3(const std_msgs :: Float64 & incoming_msg3)
{
  word data;
  msg3.data = incoming_msg3.data;
  float deg3 = msg3.data * 180 / M_PI;
  deg3 = deg3 * 14.22 + in3;
  deg3 = constrain(deg3, j3_max, j3_min);
  Move(deg3, deviceAddress[2]);
  data = feedBack(deviceAddress[2]);
  str_msg3.data = data;
  chatter3.publish( &str_msg3);
}

void msgCb4 (const std_msgs :: Float64 & incoming_msg4)
{
  word data;
  msg4.data = incoming_msg4.data;
  float deg4 = msg4.data * 180 / M_PI;
  deg4 = deg4 * -15.55 + in4;
  deg4 = constrain(deg4, j4_max, j4_min);
  Move(deg4, deviceAddress[3]);
  data = feedBack(deviceAddress[3]);
  str_msg4.data = data;
  chatter4.publish( &str_msg4);
  Serial.println("yeh");
  Serial.println(deviceAddress[3]);
}

void msgCb5(const std_msgs :: Float64 & incoming_msg5)
{
  word data;
  msg5.data = incoming_msg5.data;
  float deg5 = msg5.data * 180 / M_PI;
  deg5 = deg5 * -14.22 + in5;
  deg5 = constrain(deg5, j5_max, j5_min);
  Move(deg5, deviceAddress[4]);
  // select pin out for the mux
  digitalWrite(en,LOW);//active low
  digitalWrite(s1,LOW);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  data = feedBack(deviceAddress[4]);
  digitalWrite(en,HIGH);
  str_msg5.data = data;
  chatter5.publish( &str_msg5);
}

void msgCb6 (const std_msgs :: Float64 & incoming_msg6)
{
  word data;
  msg6.data = incoming_msg6.data;
  float deg6 = msg6.data * 180 / M_PI;
  deg6 = deg6 * 14.77 + in6;
  deg6 = constrain(deg6, j6_min, j6_max);
  Move(deg6, deviceAddress[5]);
  // select pin out for the mux
  digitalWrite(en,LOW);
  digitalWrite(s1,LOW);
  digitalWrite(s2,HIGH);
  digitalWrite(s3,LOW);
  data = feedBack(deviceAddress[5]);
  digitalWrite(en,HIGH);
  str_msg6.data = data;
  chatter6.publish( &str_msg6);
}

char s;
void servo_cb1( const std_msgs::String& cmd_msg){
  
  String s= cmd_msg.data ;
  if(s == "1")
  {
      digitalWrite(r_1, LOW);
      digitalWrite(r_2, LOW);
      digitalWrite(r_3, HIGH);
      digitalWrite(r_4, LOW);
    
  }
 
  else if(s == "2")
  {
      digitalWrite(r_1, LOW);
      digitalWrite(r_2, LOW);
      digitalWrite(r_3, LOW);
      digitalWrite(r_4, HIGH);
    
  }
  else if(s == "3")
  {

      digitalWrite(r_1, HIGH);
      digitalWrite(r_2, LOW);
      digitalWrite(r_3, LOW);
      digitalWrite(r_4, LOW);   
  }
  else if(s == "4")
  {

      digitalWrite(r_1, LOW);
      digitalWrite(r_2, HIGH);
      digitalWrite(r_3, LOW);
      digitalWrite(r_4, LOW);   
  }

  else if(s == "0") {
      digitalWrite(r_1, LOW);
      digitalWrite(r_2, LOW);
      digitalWrite(r_3, LOW);
      digitalWrite(r_4, LOW);
    
  } 
    //toggle led  
}

ros::Subscriber<std_msgs::String> sub_body("body", servo_cb1);

void Move(int x, byte address) {
  word target = x;  
  byte deviceAddress = address;
  dataH = 0x40 + (target & 0x1F);
  dataL  =(target >> 5) & 0x7F;
  Serial.write(0xAA); //tells the controller we're starting to send it commands
  Serial.write(deviceAddress);   //This is the pololu device # 
  Serial.write(dataH); //first half of the target,
  Serial.write(dataL);   //second half of the target

//  Serial.print(0xAA,HEX); //tells the controller we're starting to send it commands
//  Serial.print(deviceAddress,HEX);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
//  Serial.print(0x40 + (target & 0x1F),HEX); //first half of the target, see the pololu jrk manual for more specifics
//  Serial.print((target >> 5) & 0x7F,HEX);   //second half of the target, " " " 
//  Serial.println(); 
} 
 
word feedBack(byte address)
{
  word data;
  byte low, high;
  Serial.write(header);
  Serial.write(address);
  Serial.write(feed1);
  while(!Serial.available()){}
  low = Serial.read();
  high = Serial.read();
  data = high;
  data = data << 8 | low;

  return data;
}

ros :: Subscriber<std_msgs :: Float64 > sub1("joint0", &msgCb1);
ros :: Subscriber<std_msgs :: Float64 > sub2("joint1", &msgCb2);
ros :: Subscriber<std_msgs :: Float64 > sub3("joint2", &msgCb3);  
ros :: Subscriber<std_msgs :: Float64 > sub4("joint3", &msgCb4);
ros :: Subscriber<std_msgs :: Float64 > sub5("joint4", &msgCb5);
ros :: Subscriber<std_msgs :: Float64 > sub6("joint5", &msgCb6); 
void setup() 
{
  Serial.begin(57600);
  Serial.begin(57600);
  Serial.println("Get ready for the action!");
  delay(1000);
  //pins for controlling relay
  pinMode(r_1, OUTPUT);
  pinMode(r_2, OUTPUT);
  pinMode(r_3, OUTPUT);
  pinMode(r_4, OUTPUT);

  // pins for the mix
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(en,OUTPUT);
  Serial.println("yeh");
  Serial.println(deviceAddress[1]);
  
  Move(in1, deviceAddress[0]); 
  Move(in2, deviceAddress[1]); 
  Move(3660, deviceAddress[2]); 
  Move(in4, deviceAddress[3]); 
  Move(in5, deviceAddress[4]); 
  Move(in6, deviceAddress[5]); 
  
  nh.getHardware() -> setBaud(57600);
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.subscribe(sub6); 
  
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  nh.advertise(chatter3);
  nh.advertise(chatter4);
  nh.advertise(chatter5);
  nh.advertise(chatter6);
  

  feedBack(deviceAddress[0]);
  feedBack(deviceAddress[1]);
  feedBack(deviceAddress[2]);
  feedBack(deviceAddress[3]);
  feedBack(deviceAddress[4]);
  feedBack(deviceAddress[5]);
}

void loop() 
{
  nh.spinOnce();
  delay(10);
}
