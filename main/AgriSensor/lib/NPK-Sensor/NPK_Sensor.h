#ifndef NPK_Sensor_h
#define NPK_Sensor_h

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class NPKSensor
{
  public:

    NPKSensor();
    void setup();
    int Nitrogen();
    int Phosphorus();
    int Potassium();

};

#endif