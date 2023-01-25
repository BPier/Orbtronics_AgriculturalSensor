#include <Arduino.h>
#include <pH_Sensor.h>
#include <Moisture_Sensor.h>
#include <Temp_Sensor.h>
#include <Data_Storage.h>
#include <Time_lib.h>
#include <BluetoothConnectivity.h>

#include <NPK_Sensor.h>
#include <SoftwareSerial.h>

#include <Battery.h>

#include <OLED_Display.h>

#include <BluetoothSerial.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>

#include <WiFi.h>
#include <myWifiOTA.h>

BluetoothSerial serialBT;

// Battery Variables
#define Battery_Pin 33
Battery Battery_S(Battery_Pin);
float Battery_Value = 0.0;

// pH Variables
#define pH_Pin 4
#define pH_Power_Pin 15
pHSensor pH_S(pH_Pin,pH_Power_Pin);
float pH_Value = 0.0;

// Moisture Variable
// Moisture is displayed has Volumetric Water Content from 0-100%
#define Moist_Pin 32
#define Moist_Power_pin 13
MoistureSensor Moist_S(Moist_Pin, Moist_Power_pin);
int Moisture_Value = 0;

// Temperature Variables
#define Temp_Pin 16
#define Temp_Power_pin 18
TempSensor Temp_S(Temp_Pin,Temp_Power_pin);
float Temperature_Value = 0.0;

// Data Storage Variable
DataStorage Data_S;



// NPK Variables
NPKSensor npk;
int N = npk.Nitrogen();
int P = npk.Phosphorus();
int K = npk.Potassium();

// Bluetooth Connectivity Variable
#define BT_Switch_Pin 34
#define BT_LED_Pin 26
BluetoothConnectivity BLC(BT_Switch_Pin,BT_LED_Pin);
bool BT_Activated = false;
bool BT_Connected = false;

// Wifi Variable
myWifiOTA ota;


DataStorage DS;

// Time Management Variable
Timelib Time_l;
// char* Formated_time;
// unsigned long TimeMillis = 0;
// OLED Screen Variable
#define SPI_Power_Pin 19
OLEDDisplay OLED(SPI_Power_Pin);
const char* Bluetooth_status;
static char Battery_OLED_MESSAGE[128];

const char* DEBUG_OLED_MESSAGE;
bool Init_OK = false;

// ============== Data Reading ================
// Read the Values from the sensors, stores is in variables and write in in file
void DataReading(void *pvParameters){

  while (1) {
 
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


    vTaskDelay(500 / portTICK_PERIOD_MS);  }
}

// ============== Bluetooth ================
void BTConnect(void *pvParameters)
{
  // long currentMillisBT= 0;
  // long previousMillisBT= 0;
  byte BT_Switch_Pin_Status;
  String cmd1;
  int delayBT = 2000;
  while (1) {
    vTaskDelay(delayBT / portTICK_PERIOD_MS);
    // Serial.printf("[INFO] Bluetooth Status: ");Serial.println(Bluetooth_status);
    // currentMillisBT = millis();
    // if (currentMillisBT - previousMillisBT > 1000){     
      BT_Switch_Pin_Status = digitalRead(BT_Switch_Pin);
      if (BT_Activated == false){
        BT_Switch_Pin_Status = digitalRead(BT_Switch_Pin);
        // Serial.printf("[INFO] BT_Switch_Pin = %d\n",BT_Switch_Pin_Status);
        if (BT_Switch_Pin_Status){
          Bluetooth_status = "Start Bluetooth";
          BLC.setup();
          Bluetooth_status="Bluetooth Pairing ...";
          BT_Activated = true;
          delayBT = 100;
        }
      } else if (BT_Activated == true)
      {
        if (!BT_Switch_Pin_Status){
          Bluetooth_status = "Stop Bluetooth";
          BT_Activated = false;
          BLC.stop();
          if (WiFi.status() == WL_CONNECTED){
            WiFi.disconnect();
          }     
          vTaskDelay(5000 / portTICK_PERIOD_MS);
          Bluetooth_status = "Bluetooth OFF";
          delayBT = 2000;

        }

      }
      


      if (serialBT.available())
      { 
        Bluetooth_status="Bluetooth Connected";

        char incomingChar = serialBT.read();
        if (incomingChar != '\n'){
          cmd1 += String(incomingChar);
        }
        else {
          Serial.println(cmd1);
          if(cmd1.indexOf("Send_file")== 0){
            Serial.println(cmd1.indexOf("Send_file"));
            BLC.BT_Write();
            DS.sendFileBT(SPIFFS, "/2022-12_data.csv");
          }
          cmd1 = "";
        }

      if serialBT.read("Wifi-Connect\n"){
        Bluetooth_status = "Stop Bluetooth";
        BT_Activated = false;
        BLC.stop();
        ota.setup();
        ota.loop();
      }
      }
    // }   
    // previousMillisBT = millis();
  }

// ============== OLED Screen ================

}
void OLEDScreenDisplay(void *pvParameters)
{
  long currentMillisOLED= 0;
  long previousMillisOLED= 0;
  OLED.Clear();
  OLED.Display();
  vTaskDelay(1000 / portTICK_PERIOD_MS);  while (1)
  {
    currentMillisOLED = millis();
    if (currentMillisOLED - previousMillisOLED > 500){
      OLED.Clear();   
      OLED.WriteLine(Battery_OLED_MESSAGE,5);
  
      OLED.WriteLine(Bluetooth_status,6);
      OLED.WriteLine(DEBUG_OLED_MESSAGE,7);
      if (Init_OK){
        OLED.CurrentValues(pH_Value,Moisture_Value,Temperature_Value);
      } else{
        OLED.WriteLine("Initializing Sensor..",1);
      }
      previousMillisOLED = millis();
      OLED.Display();
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);  }
 
}
void BatteryVoltage(void *pvParameters)
{
  long currentMillisBatteryVoltage= 0;
  long previousMillisBatteryVoltage = 0;
  float Battery_Voltage = 0.0;
  int Battery_Level = 0;

  while (1)
  {
    currentMillisBatteryVoltage = millis();
    if (currentMillisBatteryVoltage - previousMillisBatteryVoltage > 500){
      // Battery_Voltage = map(analogRead(33), 0.0f, 4095.0f, 0, 3.3);
      // Battery_Voltage = analogRead(33);
      // Serial.print("Battery analog: ");
      // Serial.println(Battery_Voltage);
      // Battery_Voltage = map(Battery_Voltage, 0.0f, 4095.0f, 0, 3300);
      // Battery_Voltage = Battery_Voltage;
      // Battery_Voltage = Battery_Voltage/2*(r1+r2)/r2*Calibration_Resistor;
      Battery_Voltage = Battery_S.read();
      // Battery_Level = map(int(Battery_Voltage), 3300, 4200, 0, 100);
      Battery_Level = 
      snprintf(Battery_OLED_MESSAGE,
        255,
        PSTR("B:%0.1fV-%d%%%"),
        Battery_Voltage/1000,
        Battery_Level
      );
      previousMillisBatteryVoltage = millis();
      // if(Battery_Level<80){
      //   DEBUG_OLED_MESSAGE = "LOW BAT - Turning OFF";
      //   delay(5000);
      //   digitalWrite(15,LOW);

      //   esp_sleep_enable_timer_wakeup(5*1000000);
      //   esp_deep_sleep_start();
      // }
        
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
 
}

bool SensorsStartSequence(){
  pH_S.setup();
  delay(1000);
  DEBUG_OLED_MESSAGE = "Start Moisture";
  delay(500);
  Moist_S.setup();
  delay(1000);
  DEBUG_OLED_MESSAGE = "Start Temperature";
  delay(500);
  Temp_S.setup();
  delay(1000);
  DEBUG_OLED_MESSAGE = "Start Data";
  delay(500);
  Data_S.setup();
  delay(1000);
  DEBUG_OLED_MESSAGE = "Start Clock";
  delay(500);
  Time_l.setup();
  delay(1000);

  
  delay(2000);
  npk.setup();

  return true;
}

// ================= SETUP ====================
void setup() {
  pinMode(15, OUTPUT);
  Serial.begin(115200);
  Serial.println("======= SETUP =======");
  delay(500);
  digitalWrite(15,HIGH);
  delay(50);
  // -------------- OLED --------------
  OLED.setup();
  xTaskCreatePinnedToCore(OLEDScreenDisplay, "OLEDScreenDisplay", 5000, NULL, 5, NULL, 0);
  delay(300);

  Init_OK = SensorsStartSequence();
  DEBUG_OLED_MESSAGE = "All OK";

  // [DEBUG] Delete File
  Data_S.deleteFile(SPIFFS,"/2022-12_data.csv");
  Serial.println("=====================");




  xTaskCreatePinnedToCore(DataReading, "DataReading", 16000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(BTConnect, "BTConnect", 5000, NULL, 20, NULL, 1);
  xTaskCreatePinnedToCore(BatteryVoltage, "BatteryVoltage", 5000, NULL, 10, NULL, 1);

}



// ================= LOOP ======================
void loop() {


}
