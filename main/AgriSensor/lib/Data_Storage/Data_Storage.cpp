#include "Arduino.h"
#include "Data_Storage.h"
#include "Time_lib.h"



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
  Timelib Time_l;
  char* Formated_time = "";
  static char Formated_text[255];
  unsigned long TimeMillis = 0;
  TimeMillis = Time_l.GetTime();
  Formated_time = Time_l.FormatTime(TimeMillis);

  snprintf(Formated_text,
    255,
    PSTR("{\"Time\":\"%s\",\"pH\":%.2f,\"Moisture\":%.1f,\"Temp\":%.2f}"),
    Formated_time,
    pH,
    Moisture,
    Temp
  );

  Serial.print("[INFO] : The following data is stored: ");
  Serial.println(Formated_text);

}