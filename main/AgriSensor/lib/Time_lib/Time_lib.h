#ifndef Time_lib_h
#define Time_lib_h

#include "Arduino.h"
#include <Time_lib.h>


class Timelib
{
  public:
    Timelib();
    void setup();
    unsigned long GetTime();
    char* FormatTime(unsigned long timemillis);
  private:
    int _pin;
};

#endif