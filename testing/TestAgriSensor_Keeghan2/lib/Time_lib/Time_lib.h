#ifndef Time_lib_h
#define Time_lib_h

#include "Arduino.h"

class Timelib
{
  public:
    Timelib();
    void setup();
    unsigned long GetTime();
    String FormatTime();
};

#endif