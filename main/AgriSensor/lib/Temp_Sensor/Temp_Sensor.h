#ifndef Temp_Sensor_h
#define Temp_Sensor_h

#include "Arduino.h"
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TempSensor
{
  public:
    TempSensor(int pin, int powerpin);
    void setup();
    float read();
    void calibrate();
  private:
    int _pin;
    int _powerpin;
};

#endif