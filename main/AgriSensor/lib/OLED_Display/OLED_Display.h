#ifndef OLED_Display_h
#define OLED_Display_h

#include "Arduino.h"

class OLEDDisplay
{
  public:

    OLEDDisplay(int powerpin);
    void setup();
    void WriteLine(const char* Text, int line);
    void Clear();
    void Display();
    void CurrentValues(const float pH, const int Moisture, const float Temp, const int N, const int P, const int K);
  private:
    int _powerpin;
};

#endif