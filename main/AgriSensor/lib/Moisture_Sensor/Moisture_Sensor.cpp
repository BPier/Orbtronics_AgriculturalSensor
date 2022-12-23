#include "Arduino.h"
#include "Moisture_Sensor.h"
int Moist_Pin = 0;
int dryValue = 3500;
int wetValue = 1500;
int DryValue_Mapped = 0;
int WetValue_Mapped = 100;
float rawValue;
int mappedValue;

MoistureSensor::MoistureSensor(int pin)
{
  pinMode(pin, INPUT);
  Moist_Pin = pin;
}

void MoistureSensor::setup()
{
    Serial.begin(115200);
    (dryValue,wetValue,DryValue_Mapped,WetValue_Mapped) = (3500,1500, 0, 100);
    Serial.println("[INFO] : The Moisture sensor is set up ");
}

float MoistureSensor::read()
{
    rawValue = analogRead(_pin);
    return rawValue;
}

void MoistureSensor::calibrate()
{
    mappedValue = map(rawValue, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);

}

