#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include "ArduinoHardware.h"
#include "MovingMotorControl.h"
#include "LEDBlinker.h"
#include "DistanceSen.h"

#define front_trig 3
#define front_echo 2

#define rear_trig 7
#define rear_echo 4

#include <Dynamixel2Arduino.h>
#include <DynamixelShield.h>

#define ARDUINO_AVR_MEGA2560
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif

const uint8_t DXL_ID = 4;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

ros::NodeHandle nh;
MovingMotor DCmotor(5, 6, 8, 9, 10, 11);
DistanceSen FrontUltrasound(front_trig, front_echo);
DistanceSen RearUltrasound(rear_trig, rear_echo);


float LJ_x, LJ_y, RJ_x, RJ_y, LF3, RF3, LF2, RF2 ,RA, RB, LX, LY ;

void ArduinoCallback(const std_msgs::Float32MultiArray& joy_array)
{
    LJ_x=joy_array.data[0];
    LJ_y=joy_array.data[1];
    RJ_x=joy_array.data[2];
    RJ_y=joy_array.data[3];
    LF3=joy_array.data[4];
    RF3=joy_array.data[5];
    LF2=joy_array.data[6];
    RF2=joy_array.data[7];
    RA=joy_array.data[8];
    RB=joy_array.data[9];
    LX=joy_array.data[10];
    LY=joy_array.data[11];

    FrontUltrasound.Sensing();
    RearUltrasound.Sensing();

//    DCmotor.joystick(RJ_x,RJ_y); 
//    if(FrontUltrasound.Distance()<6 and RJ_x>0 and RJ_y>0) DCmotor.StopMoving();
//    if(RearUltrasound.Distance()<6 and RJ_x<0 and RJ_y<0) DCmotor.StopMoving();
//    DCmotor.TurnLeft(LF3,150);
//    DCmotor.TurnRight(RF3, 150);
    DCmotor.OutWater(RF2);
    DCmotor.InWater(LF2);
    DynamixelTurn(LJ_x);
        
}

ros::Subscriber<std_msgs::Float32MultiArray> sub_joystick("joystick_val_topic", ArduinoCallback);

void setup()
{
    pinMode(52,OUTPUT);
    Serial.begin(115200);
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    // ros::Subscriber sub_joystick = nh.subscribe<std_msgs::Float64MultiArray>("joystick_val_topic", 1, &ArduinoCallback);
    nh.subscribe(sub_joystick);

    DEBUG_SERIAL.begin(115200);
    dxl.begin(115200);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    dxl.ping(DXL_ID);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(DXL_ID);
    dxl.setOperatingMode(DXL_ID, OP_CURRENT);
    dxl.torqueOn(DXL_ID); 
}

void loop()
{
    nh.spinOnce();
    delay(1);
}


void DynamixelTurn(double value)
{
  if(value>0)
  {
    int value_ = int(value*1000.0);
    int x=map(value_,0,1000,200,500);
    dxl.setGoalCurrent(DXL_ID, x);
  }
  
  else if(value<0)
  {
    int value_ = int(-value*1000.0);
    int x=map(value_,0,1000,200,500);
    dxl.setGoalCurrent(DXL_ID, -x);
  }
  if(value==0) dxl.setGoalCurrent(DXL_ID,0);

}
