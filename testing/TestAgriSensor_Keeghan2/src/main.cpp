#include <npk_and_ph.h>
#include <Arduino.h>

npk_and_ph npk_ph;

void setup(){
  Serial.begin(9600);
  npk_ph.setup();
};

void loop(){
  byte n = npk_ph.Nitrogen();
  // delay(1000);
  // byte p = npk_ph.Phosphorus();
  // delay(1000);
  // byte k = npk_ph.Potassium();
  // delay(1000);
  // byte pH_reading = npk_ph.pH();
  // delay(1000);

  Serial.printf("N: %d", n);
  Serial.println();
  // Serial.printf("P: %d", p);
  // Serial.println();
  // Serial.printf("K: %d", k);
  // Serial.println();
  // Serial.printf("pH: %d", pH_reading);
  // Serial.println();
  delay(1000);
};
 

