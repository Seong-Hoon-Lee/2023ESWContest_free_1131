#include "Arduino.h"
#include "LEDBlinker.h"

LEDBlinker::LEDBlinker(long OnT1, long OffT1, unsigned long p_M_1, long OnT2, long OffT2, unsigned long p_M_2)
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  onTime1 = OnT1;
  offTime1 = OffT1;
  bright1 = 0;
  prevMillis1 = p_M_1;

  onTime2 = OnT2;
  offTime2 = OffT2;
  bright2 = 0;
  prevMillis2 = p_M_2;
}


void LEDBlinker::justLED1(int bright1)
{
  analogWrite(led1, bright1);
}

void LEDBlinker::justLED2(int bright2)
{
  analogWrite(led2, bright2);
}

void LEDBlinker::Blink1()
{
  unsigned long curMillis1 = millis();
  if(bright1 == 255)
  {
    if(curMillis1 - prevMillis1 >= onTime1)
    {
      bright1 = 0;
      prevMillis1 = curMillis1;
      analogWrite(led1, bright1);
    }
  }
  else
  {
    if(curMillis1 - prevMillis1 >= offTime1)
    {
      bright1 = 255;
      prevMillis1 = curMillis1;
      analogWrite(led1, bright1);
    }
  }
}

void LEDBlinker::Blink2()
{
  unsigned long curMillis2 = millis();
  if(bright2 == 255)
  {
    if(curMillis2 - prevMillis2 >= onTime2)
    {
      bright2 = 0;
      prevMillis2 = curMillis2;
      analogWrite(led2, bright2);
    }
  }
  else
  {
    if(curMillis2 - prevMillis2 >= offTime2)
    {
      bright2 = 255;
      prevMillis2 = curMillis2;
      analogWrite(led2, bright2);
    }
  }
}
