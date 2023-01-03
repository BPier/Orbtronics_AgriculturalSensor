#ifndef OLED_Display_h
#define OLED_Display_h

#include "Arduino.h"

class OLEDDisplay
{
  public:

    OLEDDisplay();
    void setup();
    void WriteLine(const char* Text, int line);
    void Clear();
    void Display();
    void CurrentValues(const float pH, const int Moisture, const float Temp);
  private:
    int _pin;
};

#endif