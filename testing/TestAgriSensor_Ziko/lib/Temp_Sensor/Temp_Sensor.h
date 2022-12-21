#ifndef Temp_Sensor_h
#define Temp_Sensor_h

#include "Arduino.h"

class TempSensor
{
  public:
    TempSensor(int pin);
    void setup();
    float read();
    void calibrate();
  private:
    int _pin;
};

#endif