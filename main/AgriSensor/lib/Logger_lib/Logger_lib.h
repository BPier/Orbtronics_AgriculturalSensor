#ifndef Logger_lib_h
#define Logger_lib_h

#include "Arduino.h"
#include <Data_Storage.h>

class Logger_lib
{
  public:
    Logger_lib();
    void setup();
    void logEvent(int level, char* EventDescription);
};

#endif