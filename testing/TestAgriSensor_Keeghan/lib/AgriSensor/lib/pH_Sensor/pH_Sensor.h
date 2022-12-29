#ifndef pH_Sensor_h
#define pH_Sensor_h

#include "Arduino.h"

class pHSensor
{
  public:
    pHSensor(int pin);
    void setup();
    float read();
    void calibrate();
  private:
    int _pin;
};

#endif