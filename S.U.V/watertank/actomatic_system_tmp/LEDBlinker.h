#define led1 A1
#define led2 A2

class LEDBlinker
{
private:
  int bright1;
  long onTime1, offTime1;
  uint32_t prevMillis1;

  int bright2;
  long onTime2, offTime2;
  uint32_t prevMillis2;

public:

  LEDBlinker(long OnT1, long OffT1, unsigned long p_M_1, long OnT2, long OffT2, unsigned long p_M_2);
  void justLED1(int bright_1);
  void justLED2(int bright_2);
  void Blink1();
  void Blink2();
};
