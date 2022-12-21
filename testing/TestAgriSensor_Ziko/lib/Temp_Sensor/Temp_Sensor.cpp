#include "Arduino.h"
#include "Temp_Sensor.h"
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>
int Temp_Pin = 17;

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(Temp_Pin);	
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

TempSensor::TempSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  Temp_Pin = pin;
}

void TempSensor::setup()
{
  sensors.begin();    
  Serial.print("[INFO] : The Temperature sensor is set up on pin ");
  Serial.println(Temp_Pin);
}


float TempSensor::read()
{
  // Generate a random Value between 10 and 35C to simulate soil Temperature
  // float TempValue = random(100,350);
  // TempValue = TempValue/10;
  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
  // return TempValue;
}

void TempSensor::calibrate()
{

}