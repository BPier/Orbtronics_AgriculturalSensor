#include "Arduino.h"
#include "Data_Storage.h"
#include <Time_lib.h>



DataStorage::DataStorage()
{
  // pinMode(pin, INPUT);
  // _pin = pin;
  return;
}

void DataStorage::setup()
{
    Serial.println("[INFO] : The data module is ready to be used ");
}


void DataStorage::read()
{

}

void DataStorage::writedata(float pH, float Moisture, float Temp)
{
  static char time[30];

  Serial.println("[INFO] : The following data is stored ");
  Serial.println();
}