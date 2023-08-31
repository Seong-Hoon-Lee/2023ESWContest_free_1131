class MovingMotor
{
private:
  int RightMotor_E_pin;       // 오른쪽 모터의 Enable & PWM
  int LeftMotor_E_pin;        // 왼쪽 모터의 Enable & PWM
  int RightMotor_1_pin;       // 오른쪽 모터 제어선 IN1
  int RightMotor_2_pin;       // 오른쪽 모터 제어선 IN2
  int LeftMotor_3_pin;       // 왼쪽 모터 제어선 IN3
  int LeftMotor_4_pin;  
  int Speed;
  int x_value;
  int y_value;
  int flag;
  double temp_RF3, temp_LF3;

public:

  MovingMotor(int RightMotor_E_pin_, int LeftMotor_E_pin_, int RightMotor_1_pin_, int RightMotor_2_pin_, int LeftMotor_3_pin_, int LeftMotor_4_pin_ );
  // MovingMotor(int RightMotor_1_pin_, int RightMotor_2_pin_, int LeftMotor_3_pin_, int LeftMotor_4_pin_ );
  
  void GoStraight(int Speed_);
  void GoBack(int Speed_);
  void TurnRight(double RF3, int Speed_);
  void TurnLeft(double LF3, int Speed_);
  void StopMoving();
  void joystick(double x_value, double y_value);
  void OutWater(double value);
  void InWater(double value);
  void Camera(double value);

};
