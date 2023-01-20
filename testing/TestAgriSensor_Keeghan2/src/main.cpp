#include <pH_Sensor_2.h>
#include <Arduino.h>

pHSensor pH_v;

void setup(){
  Serial.begin(9600);
  pH_v.setup();
};

void loop(){
  float pH_reading = pH_v.pH();
  Serial.printf("pH: %d", pH_reading);
  delay(2000);
};
 
