#ifndef Data_Storage_h
#define Data_Storage_h

#include "Arduino.h"

class DataStorage
{
  public:
    DataStorage();
    void setup();
    void read();
    void writedata();
  private:
    int _pin;
};

#endif