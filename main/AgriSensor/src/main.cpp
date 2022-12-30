#include <Arduino.h>
#include <pH_Sensor.h>
#include <Moisture_Sensor.h>
#include <Temp_Sensor.h>
#include <Data_Storage.h>
#include <Time_lib.h>

// pH Variables
#define pH_Pin 34
pHSensor pH_S(pH_Pin);
float pH_Value = 0.0;

// Moisture Variable
// Moisture is displayed has Volumetric Water Content from 0-100%
#define Moist_Pin 32
MoistureSensor Moist_S(Moist_Pin);
int Moisture_Value = 0;

// Temperature Variables
#define Temp_Pin 17
TempSensor Temp_S(Temp_Pin);
float Temperature_Value = 0.0;

// Data Storage Variable
DataStorage Data_S;

// Time Management Variable
Timelib Time_l;
// char* Formated_time;
// unsigned long TimeMillis = 0;

// ================= SETUP ====================
void setup() {
  Serial.begin(115200);
  Serial.println("======= SETUP =======");

  pH_S.setup();
  Moist_S.setup();
  Temp_S.setup();
  Data_S.setup();
  Time_l.setup();

  // [DEBUG] Delete File
  Data_S.deleteFile(SPIFFS,"/2022-12_data.csv");

  Serial.println("=====================");
}



// ================= LOOP ======================
void loop() {
  Serial.println("---------------------");

  // Read and display the pH Value
  pH_Value = pH_S.read();
  

  // Read and Display the Volumetric Water Content
  Moisture_Value = Moist_S.read();
 

  // Read and Diplay the soil Temperature
  Temperature_Value = Temp_S.read();
  

  // Get Time - Time is being imported in the dataStorage Library
  String time =  Time_l.FormatTime();
  // Serial.println(String("DateTime::\t")+ (" ") + time);

  // Store the data
  Data_S.writedata(pH_Value,Moisture_Value,Temperature_Value);
  //Data_S.readFile(SPIFFS, "/2022-12_data.csv");


  delay(5000);

}
