#ifndef Moisture_Sensor_h
#define Moisture_Sensor_h

#include "Arduino.h"

class MoistureSensor
{
  public:

    MoistureSensor(int pin, int PowerPin);
    void setup();
    int read();
    void calibrate();
  private:
    int _pin;
    int _powerpin;
};

#endif