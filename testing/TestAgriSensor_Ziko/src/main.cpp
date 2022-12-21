#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>
float Temp_value = 0;

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 17

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

float read_temp(){
  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}

void setup(void)
{
  sensors.begin();	// Start up the library
  Serial.begin(115200);
}

void loop(void)
{ 
  Temp_value =  read_temp();
  Serial.println(Temp_value);
  delay(3000);
  Serial.println("------------------------");
}

