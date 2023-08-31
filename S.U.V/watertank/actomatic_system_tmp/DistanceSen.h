#include "Arduino.h"

class DistanceSen
{
private:
  int trig_;
  int echo_;
  int dt_us_;
  double distance_;

public:
  DistanceSen(int trig, int echo);

  void Sensing();
  double Distance();
};
