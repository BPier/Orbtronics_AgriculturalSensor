#include "Arduino.h"
#include "Moisture_Sensor.h"


MoistureSensor::MoistureSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

void MoistureSensor::setup()
{
    Serial.println("[INFO] : The Moisture sensor is set up ");
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