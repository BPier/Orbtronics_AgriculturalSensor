#include "Arduino.h"
#include "pH_Sensor.h"
#define Offset 0//deviation compensate
unsigned long int avgValue; //Store the average value of the sensor feedback void

pHSensor::pHSensor(int pin, int powerpin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  pinMode(powerpin, OUTPUT);
  _powerpin = powerpin;
}

void pHSensor::setup()
{
    Serial.print("[INFO] : The pH sensor is set up on pin ");
    Serial.println(_pin);
}


float pHSensor::read()
{
  digitalWrite(_powerpin,HIGH);
  delay(1000);
    // Generate a random Value between 5 and 7 to simulate soil pH
  int buf[10]; //buffer for read analog
  int temp_var = 0;
  float phValue = 0;
  for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(_pin);
    Serial.printf("Ph analog Reading [%d]: %d",i,buf[i]); 
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
  for(int i=2;i<8;i++)
  {
    //take the average value of 6 center sample
    avgValue+=buf[i];
    avgValue = avgValue/6; // takes average
  }
    // Serial.println(avgValue);
    phValue=(float)avgValue*3.3/4095; //convert the analog into voltage
    // Serial.println(phValue);
    phValue=-25*phValue+56.5; //convert the voltage into pH value 
    // phValue = analogRead(SensorPin);
  // digitalWrite(_powerpin,LOW);

  return phValue;
}

void pHSensor::calibrate()
{

}