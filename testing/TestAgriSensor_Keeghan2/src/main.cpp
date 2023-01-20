#include <Arduino.h>
#include <NPK_Sensor.h>

NPKSensor npk;
int val1, val2, val3 = 0;

void setup(){
  Serial.begin(9600);
  npk.setup();
};

void loop(){
  val1 = npk.Nitrogen();
  val2 = npk.Phosphorus();
  val3 = npk.Potassium();
  Serial.printf("N: %d", val1);
  Serial.printf("P: %d", val2);
  Serial.printf("K: %d", val3);
};
 
