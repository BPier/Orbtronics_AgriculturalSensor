#include "Arduino.h"
#include "Moisture_Sensor.h"



int Moist_Pin = 0;
int dryValue = 3500;
int wetValue = 1500;
int DryValue_Mapped = 0;
int WetValue_Mapped = 100;
int MappedValue=0;
int moistReadings[10];
int buf[10];
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

  for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(Moist_Pin); delay(10);
  }
  for(int i=0;i<9;i++) //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  for(int i=2;i<8;i++) //take the average value of 6 center sample
  {
    total+=buf[i];
    Serial.println("The total is");
    Serial.println(total);
  }
  avg_moist = total/6;
  MappedValue = map(avg_moist, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);
  total = 0;
  return MappedValue;

}

void MoistureSensor::calibrate()
{

}

