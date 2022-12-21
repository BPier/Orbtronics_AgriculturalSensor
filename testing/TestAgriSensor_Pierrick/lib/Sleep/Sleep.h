#ifndef Sleep_h
#define Sleep_h

#include "Arduino.h"

class Sleep
{
  public:
    Sleep(int pin);
    void PrintTime(unsigned long millisOffset);
    void BoardSleep(unsigned long sleepMillis);
    unsigned long offsetMillis(unsigned long millisOffset);
  private:
    int _pin;
};

#endif