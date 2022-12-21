#include "Arduino.h"
#include "pH_Sensor.h"
int pH_Pin = 0;

pHSensor::pHSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  pH_Pin = pin;
}

void pHSensor::setup()
{
    Serial.print("[INFO] : The pH sensor is set up on pin ");
    Serial.println(pH_Pin);
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