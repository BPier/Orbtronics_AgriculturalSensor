#include "Arduino.h"
#include "pH_Sensor.h"
#define SensorPin 34 //pH meter Analog output to Arduino Analog Input 0

pHSensor pH_S(SensorPin);

void setup()
{
  pH_S.setup();
  Serial.begin(115200);
  Serial.println("Ready"); //Test the serial monitor
}

void loop()
{
  float pH = pH_S.read();
  Serial.print(" pH:");
  Serial.print(pH,2); 
  Serial.println("");
  delay(1000);
}

