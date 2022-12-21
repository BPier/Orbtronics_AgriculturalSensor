#include "Arduino.h"
#include "Moisture_Sensor.h"
int Moist_Pin = 0;

MoistureSensor::MoistureSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  Moist_Pin = pin;
}

void MoistureSensor::setup()
{
    Serial.print("[INFO] : The Moisture sensor is set up on pin ");
    Serial.println(Moist_Pin);
}


float MoistureSensor::read()
{
    // Generate a random Value between 0 and 100 to simulate soil moisture content
    float MoistureValue = random(0,100);
    return MoistureValue;
}

void MoistureSensor::calibrate()
{

}