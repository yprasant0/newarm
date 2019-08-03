#define serialCount 20
#define step 10

#define j1_min 175
#define j1_max 3365

#define j2_min 450
#define j2_max 3445

#define j3_min 3800
#define j3_max 1410

#define j4_min 4095
#define j4_max 200

#define j5_min 3425
#define j5_max 10

#define j6_min 60
#define j6_max 4050

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

void Move(int x, byte address) {
  word target = x;
  Serial.println(target);  
  byte deviceAddress = address;
  dataH = 0x40 + (target & 0x1F);
  dataL  =(target >> 5) & 0x7F;
  Serial1.write(0xAA); //tells the controller we're starting to send it commands
  Serial1.write(deviceAddress);   //This is the pololu device # 
  Serial1.write(dataH); //first half of the target,
  Serial1.write(dataL);   //second half of the target

//  Serial.print(0xAA,HEX); //tells the controller we're starting to send it commands
//  Serial.print(deviceAddress,HEX);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
//  Serial.print(0x40 + (target & 0x1F),HEX); //first half of the target, see the pololu jrk manual for more specifics
//  Serial.print((target >> 5) & 0x7F,HEX);   //second half of the target, " " " 
//  Serial.println(); 
}  
void feedBack(byte address)
{
  word data;
  byte low, high;
  Serial1.write(header);
  Serial1.write(address);
  Serial1.write(feed1);
  while(!Serial1.available()){}
  low = Serial1.read();
  high = Serial1.read();
  data = high;
  data = data << 8 | low;
  Serial.println(data);
}
void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Get ready for the action!");
  delay(1000);
  Move(in1, deviceAddress[0]); 
  Move(in2, deviceAddress[1]); 
  Move(in3, deviceAddress[2]); 
  Move(in4, deviceAddress[3]); 
  Move(in5, deviceAddress[4]); 
  Move(in6, deviceAddress[5]); 

//  feedBack(deviceAddress[0]);
//  feedBack(deviceAddress[1]);
//  feedBack(deviceAddress[2]);
//  feedBack(deviceAddress[3]);
//  feedBack(deviceAddress[4]);
//  feedBack(deviceAddress[5]);
}

void loop() 
{
  if (Serial.available()>0)
  {
    char inByte = Serial.read();

    if(inByte == '1')
    {
      in1 += step;
      in1 = constrain(in1, j1_min, j1_max);
      Move(in1, deviceAddress[0]);
    }
    else if(inByte == '2')
    {
      in1 -= step;
      in1 = constrain(in1, j1_min, j1_max);
      Move(in1, deviceAddress[0]);
    }

    else if(inByte == '3')
    {
      in2 += step;
      in2 = constrain(in2, j2_min, j2_max);
      Move(in2, deviceAddress[1]);
    }
    else if(inByte == '4')
    {
      in2 -= step;
      in2 = constrain(in2, j2_min, j2_max);
      Move(in2, deviceAddress[1]);
    }

    else if(inByte == '5')
    {
      in3 += step;
      in3 = constrain(in3, j3_max, j3_min);
      Move(in3, deviceAddress[2]);
    }
    else if(inByte == '6')
    {
      in3 -= step;
      in3 = constrain(in3, j3_max, j3_min);
      Move(in3, deviceAddress[2]);
    }

     else if(inByte == '7')
    {
      in4 += step;
      in4 = constrain(in4, j4_max, j4_min);
      Move(in4, deviceAddress[3]);
    }
    else if(inByte == '8')
    {
      in4 -= step;
      in4 = constrain(in4, j4_max, j4_min);
      Move(in4, deviceAddress[3]);
    }
         else if(inByte == 'a')
    {
      in5 += step;
      in5 = constrain(in5, j5_max, j5_min);
      Move(in5, deviceAddress[4]);
    }
    else if(inByte == 'b')
    {
      in5 -= step;
      in5 = constrain(in5, j5_max, j5_min);
      Move(in5, deviceAddress[4]);
    }


    else if(inByte == 'c')
    {
      in6 += step;
      in6 = constrain(in6, j6_min, j6_max);
      Move(in6, deviceAddress[5]);
    }
    else if(inByte == 'd')
    {
      in6 -= step;
      in6 = constrain(in6, j6_min, j6_max);
      Move(in6, deviceAddress[5]);
    }
    
  }
  /*Move(input0Scaled, deviceAddress[0]);
  Move(input1Scaled, deviceAddress[1]);
  Move(input1Scaled, deviceAddress[2]);
  Move(input1Scaled, deviceAddress[3]);
  Move(input1Scaled, deviceAddress[4]);
  Move(input1Scaled, deviceAddress[5]);
  feedBack(deviceAddress[0]);
  feedBack(deviceAddress[1]);
  feedBack(deviceAddress[2]);
  feedBack(deviceAddress[3]);
  feedBack(deviceAddress[4]);
  feedBack(deviceAddress[5]);*/
  delay(1);
}
