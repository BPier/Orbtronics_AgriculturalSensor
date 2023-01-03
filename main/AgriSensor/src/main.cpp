#include <Arduino.h>
#include <pH_Sensor.h>
#include <Moisture_Sensor.h>
#include <Temp_Sensor.h>
#include <Data_Storage.h>
#include <Time_lib.h>
#include <BluetoothConnectivity.h>

#include <OLED_Display.h>

#include <BluetoothSerial.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>

BluetoothSerial serialBT;


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

// Bluetooth Connectivity Variable
BluetoothConnectivity BLC;
const char* Bluetooth_status;

DataStorage DS;

// OLED Screen Variable
OLEDDisplay OLED;


// ============== Data Reading ================
void DataReading(void *pvParameters){
  // Parameters for Time loop
  long currentMillisDataReading = 0;
  long previousMillisDataReading = 0;
  while (1) {
    currentMillisDataReading = millis();
    
    if (currentMillisDataReading - previousMillisDataReading > 5000){
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

   



      // Data_S.readFile(SPIFFS, "/2022-12_data.csv");
      previousMillisDataReading = millis();

    }
    delay(1);
  }
}


void BTConnect(void *pvParameters)
{
 
  while (1) {
    Bluetooth_status="Bluetooth Pairing ...";
    delay(1);
    BLC.BT_Write();
  }

}
void OLEDScreenDisplay(void *pvParameters)
{
  long currentMillisOLED= 0;
  long previousMillisOLED= 0;
  OLED.Clear();
  OLED.WriteLine("Initializing Sensor..",1);
  OLED.WriteLine("Starting Bluetooth...",6);
  OLED.Display();
  delay(1000);
  while (1)
  {
    currentMillisOLED = millis();
    if (currentMillisOLED - previousMillisOLED > 500 && currentMillisOLED > 5500){
      OLED.Clear();
      OLED.CurrentValues(pH_Value,Moisture_Value,Temperature_Value);

      OLED.WriteLine(Bluetooth_status,6);
      previousMillisOLED = millis();
      OLED.Display();
    }
    delay(1);
  }
 
}
// ================= SETUP ====================
void setup() {
  Serial.begin(115200);
  Serial.println("======= SETUP =======");

  // -------------- OLED --------------
  OLED.setup();
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 8);
  // // Display static text
  // display.println("Initializing ...");
  // display.display(); 
// ---------------------------------------

  pH_S.setup();
  Moist_S.setup();
  Temp_S.setup();
  Data_S.setup();
  Time_l.setup();
  BLC.setup();

  // [DEBUG] Delete File
  Data_S.deleteFile(SPIFFS,"/2022-12_data.csv");

  Serial.println("=====================");




  xTaskCreatePinnedToCore(DataReading, "DataReading", 16000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(BTConnect, "BTConnect", 5000, NULL, 9, NULL, 1);
  xTaskCreatePinnedToCore(OLEDScreenDisplay, "OLEDScreenDisplay", 5000, NULL, 9, NULL, 1);

}



// ================= LOOP ======================
void loop() {
  BLC.BT_Write();
  DS.sendFileBT(SPIFFS, "/2022-12_data.csv");
  delay(5000);

}
