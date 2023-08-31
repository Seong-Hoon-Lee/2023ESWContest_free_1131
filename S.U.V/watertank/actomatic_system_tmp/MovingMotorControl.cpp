#include "Arduino.h"
#include "MovingMotorControl.h"

MovingMotor::MovingMotor(int RightMotor_E_pin_, int LeftMotor_E_pin_, int RightMotor_1_pin_, int RightMotor_2_pin_, int LeftMotor_3_pin_, int LeftMotor_4_pin_ )
{
  RightMotor_E_pin = RightMotor_E_pin_;       
  LeftMotor_E_pin = LeftMotor_E_pin_;        
  RightMotor_1_pin = RightMotor_1_pin_;       
  RightMotor_2_pin = RightMotor_2_pin_;       
  LeftMotor_3_pin = LeftMotor_3_pin_;      
  LeftMotor_4_pin = LeftMotor_4_pin_ ;    

  Speed = 0;
  x_value = 0;
  y_value = 0;
  flag = 0;
  temp_RF3=temp_LF3=0;

  pinMode(RightMotor_E_pin, OUTPUT);        
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
}

void MovingMotor::GoStraight(int Speed_)
{
  Speed = Speed_;
    
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);

  analogWrite(RightMotor_E_pin, Speed);
  analogWrite(LeftMotor_E_pin, Speed + 5);
}

void MovingMotor::GoBack(int Speed_)
{
  Speed = Speed_;

  digitalWrite(RightMotor_1_pin, LOW);
  digitalWrite(RightMotor_2_pin, HIGH);
  digitalWrite(LeftMotor_3_pin, LOW);
  digitalWrite(LeftMotor_4_pin, HIGH);
    
  analogWrite(RightMotor_E_pin, Speed+10);
  analogWrite(LeftMotor_E_pin, Speed+10);
}

void MovingMotor::TurnRight(double RF3, int Speed_)
{
  if(RF3==0 and temp_RF3!=0) {MovingMotor::StopMoving(); temp_RF3=0; return;}
  else if (RF3!=0)
  {
    Speed = Speed_;

    int R_motor = 0;
    int L_motor = 1;
  
    digitalWrite(RightMotor_1_pin, R_motor);
    digitalWrite(RightMotor_2_pin, !R_motor);
    digitalWrite(LeftMotor_3_pin, L_motor);
    digitalWrite(LeftMotor_4_pin, !L_motor);               
     
    analogWrite(RightMotor_E_pin, max(Speed,50));  // 우측 모터 속도값
    analogWrite(LeftMotor_E_pin, min(Speed,255));
    temp_RF3=RF3;
  }
}

void MovingMotor::TurnLeft(double LF3, int Speed_)
{
  if(LF3==0 and temp_LF3!=0) {MovingMotor::StopMoving(); temp_LF3=0; return;}
  else if (LF3!=0)
  {
    Speed = Speed_;
    int R_motor = 1;
    int L_motor = 0;
  
    digitalWrite(RightMotor_1_pin, R_motor);
    digitalWrite(RightMotor_2_pin, !R_motor);
    digitalWrite(LeftMotor_3_pin, L_motor);
    digitalWrite(LeftMotor_4_pin, !L_motor);
     
    analogWrite(RightMotor_E_pin, min(Speed,255));  // 우측 모터 속도값
    analogWrite(LeftMotor_E_pin, max(Speed,50));   // 좌측 모터 속도값   
    temp_LF3=LF3;
  }
}

void MovingMotor::StopMoving()
{
  MovingMotor::GoStraight(0);
}

void MovingMotor::joystick(double x_value_, double y_value_)
{
  x_value = int(x_value_*1000.0);
  y_value = int(y_value_*1000.0);

  if(x_value >= 0 && y_value > 0) // 1 사분면
  {
    int x = map(x_value, 0, 1000, 150, 230);
    int y = map(y_value, 0, 1000, 150, 230);
  
    int L_Speed = int(sqrt(x*x + y*y));
    int R_Speed = y;
  
    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, HIGH);
    digitalWrite(LeftMotor_4_pin, LOW);
  
    analogWrite(RightMotor_E_pin, L_Speed);
    analogWrite(LeftMotor_E_pin, R_Speed);
 
  }
  else if(x_value < 0 && y_value >= 0) // 2 사분면
  {
    int x = map(-x_value, 0, 1000, 150, 230);
    int y = map(y_value, 0, 1000, 150, 230);

    int L_Speed = y;
    int R_Speed = int(sqrt(x*x + y*y));

    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, HIGH);
    digitalWrite(LeftMotor_4_pin, LOW);

    analogWrite(RightMotor_E_pin, L_Speed);
    analogWrite(LeftMotor_E_pin, R_Speed);
  }
  else if(x_value <= 0 && y_value < 0) // 3 사분면
  {
    int x = map(-x_value, 0, 1000, 150, 230);
    int y = map(-y_value, 0, 1000, 150, 230);

    int L_Speed = y;
    int R_Speed = int(sqrt(x*x + y*y));

    digitalWrite(RightMotor_1_pin, LOW);
    digitalWrite(RightMotor_2_pin, HIGH);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, HIGH);

    analogWrite(RightMotor_E_pin, L_Speed);
    analogWrite(LeftMotor_E_pin, R_Speed);
  }
  else if(x_value > 0 && y_value <= 0) // 4 사분면
  {
    int x = map(x_value, 0, 1000, 150, 230);
    int y = map(-y_value, 0, 1000, 150, 230);

    int L_Speed = int(sqrt(x*x + y*y));
    int R_Speed = y;

    digitalWrite(RightMotor_1_pin, LOW);
    digitalWrite(RightMotor_2_pin, HIGH);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, HIGH);

    analogWrite(RightMotor_E_pin, L_Speed);
    analogWrite(LeftMotor_E_pin, R_Speed);
  }
  else if(x_value == 0 && y_value == 0)
  {
    MovingMotor::StopMoving();
  }
}

void MovingMotor::OutWater(double value)
{
  int x = map(value, 0, 1000, 100, 250);
  
  Speed = x;
    
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);

  analogWrite(RightMotor_E_pin, Speed);
  if(value==0)
  {
    analogWrite(RightMotor_E_pin, value);
  }
}

void MovingMotor::InWater(double value)
{
  int x = map(value, 0, 1000, 100, 250);
  
  Speed = x;
    
  digitalWrite(LeftMotor_3_pin, LOW);
  digitalWrite(LeftMotor_4_pin, HIGH);

  analogWrite(LeftMotor_E_pin, Speed);
  if(value==0)
  {
    analogWrite(LeftMotor_E_pin, value);
  }
}
