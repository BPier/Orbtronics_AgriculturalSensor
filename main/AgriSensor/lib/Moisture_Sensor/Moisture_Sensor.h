#ifndef Moisture_Sensor_h
#define Moisture_Sensor_h

#include "Arduino.h"

class MoistureSensor
{
  public:

    MoistureSensor(int pin);
    void setup();
    int read();
    void calibrate();
  private:
    int _pin;
};

#endif