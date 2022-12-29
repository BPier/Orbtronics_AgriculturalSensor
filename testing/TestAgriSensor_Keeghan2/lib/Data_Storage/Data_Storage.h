#ifndef Data_Storage_h
#define Data_Storage_h

#include "Arduino.h"
#include "Time_lib.h"


class DataStorage
{
  public:
    DataStorage();
    void setup();
    void read();
    void writedata(float pH, float Moisture, float Temp);
  private:
    int _pin;
};

#endif