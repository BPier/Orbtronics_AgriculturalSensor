#ifndef Moisture_Sensor_h
#define Moisture_Sensor_h

#include "Arduino.h"

class MoistureSensor
{
  public:

    MoistureSensor(int pin);
    void setup();
    float read();
    void calibrate();
  private:
    int _pin;
};

#endif