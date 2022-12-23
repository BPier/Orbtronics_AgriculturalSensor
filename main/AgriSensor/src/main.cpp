#include <Arduino.h>
#include <pH_Sensor.h>
#include <Moisture_Sensor.h>
#include <Temp_Sensor.h>
#include <Data_Storage.h>
#include <Time_lib.h>

// pH Variables
#define pH_Pin 33
pHSensor pH_S(pH_Pin);
float pH_Value = 0.0;

// Moisture Variable
// Moisture is displayed has Volumetric Water Content from 0-100%
#define Moist_Pin 35
MoistureSensor Moist_S(Moist_Pin);
float Moisture_Value = 0.0;

// Temperature Variables
#define Temp_Pin 25
TempSensor Temp_S(Temp_Pin);
float Temperature_Value = 0.0;

// Data Storage Variable
DataStorage Data_S;

// Time Management Variable
Timelib Time_l;
char* Formated_time = "EMPTY";
unsigned long TimeMillis = 0;

// ================= SETUP ====================
void setup() {
  Serial.begin(115200);
  Serial.println("======= SETUP =======");

  pH_S.setup();
  Moist_S.setup();
  Temp_S.setup();
  Data_S.setup();

  Serial.println("=====================");
}



// ================= LOOP ======================
void loop() {
  Serial.println("---------------------");

  // Read and display the pH Value
  pH_Value = pH_S.read();
  Serial.print("[DATA] - Soil pH is ");
  Serial.println(pH_Value,1);

  // Read and Display the Volumetric Water Content
  Moisture_Value = Moist_S.read();
  Serial.print("[DATA] - Soil VWC (Volumetric Water Content) is ");
  Serial.print(Moisture_Value,0);
  Serial.println("%");

  // Read and Diplay the soil Temperature
  Temperature_Value = Temp_S.read();
  Serial.print("[DATA] - Soil Temperature is ");
  Serial.print(Temperature_Value,1);
  Serial.println("°C");

  // Get Time
  TimeMillis = Time_l.GetTime();
  Formated_time = Time_l.FormatTime(TimeMillis);
  Serial.print("[INFO] - Time is ");
  Serial.println(Formated_time);

  // Store the data
  Data_S.writedata(pH_Value,Moisture_Value,Temperature_Value);


  delay(5000);

}
