#include <Arduino.h>
#include <pH_Sensor.h>
#include <Moisture_Sensor.h>

// pH Variables
pHSensor pH_S(33);
float pH_Value = 0.0;

// Moisture Variable
// Moisture is displayed has Volumetric Water Content from 0-100%
MoistureSensor Moist_S(35);
float Moisture_Value = 0.0;

void setup() {
  Serial.begin(115200);
  Serial.println("======= SETUP =======");

  pH_S.setup();
  Moist_S.setup();

  Serial.println("=====================");
}

void loop() {
  Serial.println("---------------------");

  // Read and display the pH Value
  pH_Value = pH_S.read();
  Serial.print("[DATA] - Soil pH is ");
  Serial.println(pH_Value);

  // Read and Display the Volumetric Water Content
  Moisture_Value = Moist_S.read();
  Serial.print("[DATA] - Soil VWC (Volumetric Water Content) is ");
  Serial.print(Moisture_Value,0);
  Serial.println("%");


  delay(5000);

}
