#include "Arduino.h"
#include "DistanceSen.h"

DistanceSen::DistanceSen(int trig, int echo)
{
  trig_ = trig;
  echo_ = echo;
  pinMode(trig_, OUTPUT);
  pinMode(echo_, INPUT);

  dt_us_ = 0;
  distance_ = 0.0;
}

void DistanceSen::Sensing()
{
  digitalWrite(trig_,LOW); 
  delayMicroseconds(2);
  digitalWrite(trig_,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_,LOW);
  dt_us_ = pulseIn(echo_,HIGH);
  distance_ = dt_us_/58.2;
}

double DistanceSen::Distance()
{
  return distance_;
}
