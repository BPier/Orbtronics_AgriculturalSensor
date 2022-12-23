#include "Arduino.h"
#define SensorPin 34 //pH meter Analog output to Arduino Analog Input 0
#define Offset -3.24 //deviation compensate
unsigned long int avgValue; //Store the average value of the sensor feedback void

void setup()
{
pinMode(13,OUTPUT);
Serial.begin(115200);
Serial.println("Ready"); //Test the serial monitor
}

void loop()
{
  int buf[10]; //buffer for read analog
  int temp_var = 0;
  for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(SensorPin); 
    //Serial.println(buf[i]);
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
    avgValue = avgValue/6;
    Serial.println(avgValue);
    float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
    Serial.println(phValue);
    phValue=3.5*phValue+Offset; //convert the millivolt into pH value 
    Serial.print(" pH:");
    Serial.print(phValue,2); 
    Serial.println(""); 
    digitalWrite(13,HIGH); 
    delay(800);
    digitalWrite(13,LOW);
}

