#include <Arduino.h>
#define moisture_sensor 32 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

int dryValue = 3500;
int wetValue = 1500;
int DryValue_Mapped = 0;
int WetValue_Mapped = 100;

void setup() {
  Serial.begin(115200);
}
void loop() {
  int rawValue = analogRead(moisture_sensor);
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(" | ");

  int MappedValue = map(rawValue, dryValue, wetValue, DryValue_Mapped, WetValue_Mapped);
  
  Serial.print("Moisture Percentage: ");
  Serial.print(MappedValue);
  Serial.println("%");
  

  delay(500);
  
}