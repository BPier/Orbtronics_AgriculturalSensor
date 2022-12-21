#include "Arduino.h"
#include "Temp_Sensor.h"
int Temp_Pin = 0;

TempSensor::TempSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  Temp_Pin = pin;
}

void TempSensor::setup()
{
    Serial.print("[INFO] : The Temperature sensor is set up on pin ");
    Serial.println(Temp_Pin);
}


float TempSensor::read()
{
    // Generate a random Value between 10 and 35C to simulate soil Temperature
    float TempValue = random(100,350);
    TempValue = TempValue/10;
    return TempValue;
}

void TempSensor::calibrate()
{

}