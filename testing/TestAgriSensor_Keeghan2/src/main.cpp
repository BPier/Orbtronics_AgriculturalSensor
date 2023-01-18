#include <NPK_Sensor.h>
#include <Arduino.h>

NPKSensor Nitrogen;
NPKSensor Phosphorus;
NPKSensor Potassium;

void setup(){
  Serial.begin(9600);
}
void loop(){
  int n_value = NPKSensor.Nitrogen();
  int p_value = NPKSensor.Phospohrus();
  int k_value = NPKSensor.Potassium();
  

}