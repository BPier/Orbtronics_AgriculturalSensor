#include "Arduino.h"
#include <Temp_Sensor.h>

// Temperature Variables
#define Temp_Pin 17
TempSensor Temp_S(Temp_Pin);
float Temperature_Value = 0.0;


void setup(void)
{
  // sensors1.begin();	// Start up the library
  Temp_S.setup();
  Serial.begin(115200);
}

void loop(void)
{ 
  Serial.println("------------------------");
  Temperature_Value = Temp_S.read();
  Serial.print("Temperature from Library :");Serial.println(Temperature_Value);
  delay(3000);
}