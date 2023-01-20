#ifndef pH_Sensor_2_h
#define pH_Sensor_2_h

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class pHSensor
{
  public:

    pHSensor();
    void setup();
    int pH();
};

#endif