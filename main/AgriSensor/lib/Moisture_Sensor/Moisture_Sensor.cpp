#include "Arduino.h"
#include "Moisture_Sensor.h"


int Moist_Pin = 0;
int dryValue = 3500;
int wetValue = 1500;
int DryValue_Mapped = 0;
int WetValue_Mapped = 100;
int MappedValue=0;
int moistReadings[10];
int avg_moist = 0;
int total = 0;

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

int MoistureSensor::read()
{
    for (int i = 0; i < 10; i++) {
        int rawValue = analogRead(Moist_Pin);
        moistReadings[i] = rawValue;
        delay(10);
        }
    avg_moist = (moistReadings[0]+moistReadings[1]+moistReadings[2]+moistReadings[3]+moistReadings[4]+moistReadings[5]+moistReadings[6]+moistReadings[7]+moistReadings[8]+moistReadings[9])/10;
  MappedValue = map(avg_moist, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);
  return MappedValue;
}

void MoistureSensor::calibrate()
{
    
}

