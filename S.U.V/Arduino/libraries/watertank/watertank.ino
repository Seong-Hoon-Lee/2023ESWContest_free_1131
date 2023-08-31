#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include "ArduinoHardware.h"
#include "MovingMotorControl.h"
#include "LEDBlinker.h"
#include "DistanceSen.h"

#define front_trig 3
#define front_echo 2

#define rear_trig 50
#define rear_echo 4

ros::NodeHandle nh;
MovingMotor DCmotor(5, 6, 8, 9, 10, 11);
MovingMotor WaterPump(12, 13, 44, 45, 34, 35);
MovingMotor CameraMotor(22,7,24,26,48,49 );
DistanceSen FrontUltrasound(front_trig, front_echo);
DistanceSen RearUltrasound(rear_trig, rear_echo);
LEDBlinker Light(50);

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
    if(LY){ Light.justLED1(LY); }

    FrontUltrasound.Sensing();
    RearUltrasound.Sensing();

    DCmotor.joystick(RJ_x,RJ_y); 
    if(FrontUltrasound.Distance()<6 and RJ_x>0 and RJ_y>0) DCmotor.StopMoving();
    if(RearUltrasound.Distance()<6 and RJ_x<0 and RJ_y<0) DCmotor.StopMoving();
    DCmotor.TurnLeft(LF3,150);
    DCmotor.TurnRight(RF3,150);
    WaterPump.OutWater(RF2);
    WaterPump.InWater(LF2);
    CameraMotor.Camera(LJ_x);   
    
}

ros::Subscriber<std_msgs::Float32MultiArray> sub_joystick("joystick_val_topic", ArduinoCallback);

void setup()
{
    pinMode(52,OUTPUT);
    Serial.begin(115200);
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub_joystick);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
