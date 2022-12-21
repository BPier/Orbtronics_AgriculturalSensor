#include "Arduino.h"
#include "pH_Sensor.h"


pHSensor::pHSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

void pHSensor::setup()
{
    Serial.println("[INFO] : The pH sensor is set up ");
}


float pHSensor::read()
{
    // Generate a random Value between 5 and 7 to simulate soil pH
    float pHValue = random(500,700);
    pHValue = pHValue/100;
    return pHValue;
}

void pHSensor::calibrate()
{

}