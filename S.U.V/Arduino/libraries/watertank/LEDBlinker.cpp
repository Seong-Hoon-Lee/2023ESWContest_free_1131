#include "Arduino.h"
#include "LEDBlinker.h"

LEDBlinker::LEDBlinker(int pin)
{
  pin_ = pin;
  pinMode(pin_, OUTPUT);
  bright1 = 0;
  tmp=0;
}


void LEDBlinker::justLED1(int bright_1)
{
  if(bright_1==1 and tmp==0)  {digitalWrite(pin_, HIGH); tmp=1;}
  else if(bright_1==1 and tmp==1)  {digitalWrite(pin_, LOW); tmp=0;}
}
