#ifndef npk_and_ph_h
#define npk_and_ph_h

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class npk_and_ph
{
  public:

    npk_and_ph();
    void setup();
    int Nitrogen();
    int Phosphorus();
    int Potassium();
    int pH();


};

#endif