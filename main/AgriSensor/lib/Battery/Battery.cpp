#include "Battery.h"
#include "Battery.h"
#define Offset 0//deviation compensate
int BatteryPin = 0;

Battery::Battery(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  BatteryPin = pin;
}

void Battery::setup()
{
    Serial.print("[INFO] : The pH sensor is set up on pin ");
    Serial.println(BatteryPin);
}


float Battery::read()
{
  unsigned long int avgValueBattery =0; //Store the average value of the sensor feedback void

  float Battery_Voltage = 0.0;

  int r1 = 33000;
  int r2 = 21000;
  float Calibration_Resistor = 1.14*1.12;
    // Generate a random Value between 5 and 7 to simulate soil pH
  int buf[10]; //buffer for read analog
  int temp_var = 0;
  for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(BatteryPin); 
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
  for(int i=2;i<8;i++) //take the average value of 6 center sample
    avgValueBattery+=buf[i];
    avgValueBattery = avgValueBattery/6; // takes average
    Serial.println(avgValueBattery);
    Battery_Voltage=float(avgValueBattery)*3300/4095; //convert the analog into voltage
    Serial.println(Battery_Voltage);

    Battery_Voltage = Battery_Voltage/2*(r1+r2)/r2*Calibration_Resistor;
    Serial.println(Battery_Voltage);
  return Battery_Voltage;
}

void Battery::calibrate()
{

}