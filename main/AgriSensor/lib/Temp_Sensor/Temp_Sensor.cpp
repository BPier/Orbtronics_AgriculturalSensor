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

TempSensor::TempSensor(int pin,int powerpin)
{
  pinMode(pin, INPUT);
  pinMode(powerpin, OUTPUT);
  _powerpin = powerpin;
  _pin = pin;
  Temp_Pin = pin;

}

void TempSensor::setup()
{
  sensors.begin();    
  Serial.printf("[INFO] : The Temperature sensor is set up on pin %d and power by pin %d",_pin,_powerpin);
  Serial.println(_pin);
  digitalWrite(_powerpin,LOW);

}


float TempSensor::read()
{
  // Generate a random Value between 10 and 35C to simulate soil Temperature
  // float TempValue = random(100,350);
  // TempValue = TempValue/10;
  // Send the command to get temperatures
  digitalWrite(_powerpin,HIGH);
  delay(100);
  sensors.requestTemperatures(); 
  float ReturnTemp = sensors.getTempCByIndex(0);
  // digitalWrite(_powerpin,LOW);

  return ReturnTemp;
  // return TempValue;
}

void TempSensor::calibrate()
{

}