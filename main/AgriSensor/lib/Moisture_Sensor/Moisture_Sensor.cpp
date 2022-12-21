#include "Arduino.h"
#include "Moisture_Sensor.h"
<<<<<<< Updated upstream
int Moist_Pin = 0;
=======

int dryValue;
int wetValue;
int DryValue_Mapped;
int WetValue_Mapped;
float rawValue;
int mappedValue;
>>>>>>> Stashed changes

MoistureSensor::MoistureSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  Moist_Pin = pin;
}

void MoistureSensor::setup()
{
<<<<<<< Updated upstream
    Serial.print("[INFO] : The Moisture sensor is set up on pin ");
    Serial.println(Moist_Pin);
=======
    Serial.begin(115200);
    (dryValue,wetValue,DryValue_Mapped,WetValue_Mapped) = (3500,1500, 0, 100);
    Serial.println("[INFO] : The Moisture sensor is set up ");
>>>>>>> Stashed changes
}

float MoistureSensor::read()
{
    rawValue = analogRead(_pin);
    return rawValue;
}

void MoistureSensor::calibrate()
{
    mappedValue = map(rawValue, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);
    return mappedValue;
}

