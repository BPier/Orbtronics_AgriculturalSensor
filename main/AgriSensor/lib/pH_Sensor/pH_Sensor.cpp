#include "Arduino.h"
#include "pH_Sensor.h"
#define Offset 0//deviation compensate
unsigned long int avgValue; //Store the average value of the sensor feedback void
int SensorPin = 0;

pHSensor::pHSensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  SensorPin = pin;
}

void pHSensor::setup()
{
    Serial.print("[INFO] : The pH sensor is set up on pin ");
    Serial.println(SensorPin);
}


float pHSensor::read()
{
    // Generate a random Value between 5 and 7 to simulate soil pH
  int buf[10]; //buffer for read analog
  int temp_var = 0;
  for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(SensorPin); 
    delay(10);
  }
  for(int i=0;i<9;i++) //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp_var=buf[i];
        buf[i]=buf[j];
        buf[j]=temp_var;
      }
    }
  }
  int avgValue=0;
  for(int i=2;i<8;i++) //take the average value of 6 center sample
    avgValue+=buf[i];
    avgValue = avgValue/6; // takes average
    // Serial.println(avgValue);
    float phValue=(float)avgValue*3.23/4095; //convert the analog into voltage
    // Serial.println(phValue);
    phValue=-25*phValue+56.5; //convert the voltage into pH value 
  return phValue;
}

void pHSensor::calibrate()
{

}