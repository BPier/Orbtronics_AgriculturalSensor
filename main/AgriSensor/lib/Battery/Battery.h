#ifndef Battery_h
#define Battery_h

#include "Arduino.h"

class Battery
{
  public:
    Battery(int pin);
    void setup();
    float read();
    void calibrate();
  private:
    int _pin;
};

#endif