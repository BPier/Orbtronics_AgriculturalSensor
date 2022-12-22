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
    // rawValue = analogRead(_pin);
    // return rawValue;
}

void MoistureSensor::calibrate()
{
    // mappedValue = map(rawValue, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);
    // return mappedValue;
}

