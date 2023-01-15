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

DataStorage DS;

// OLED Screen Variable
OLEDDisplay OLED;
const char* Bluetooth_status;
static char Battery_OLED_MESSAGE[128];

const char* DEBUG_OLED_MESSAGE;
bool Init_OK = false;

// ============== Data Reading ================
// Read the Values from the sensors, stores is in variables and write in in file
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

// ============== Bluetooth ================
void BTConnect(void *pvParameters)
{
  String cmd1;
  while (1) {
    Bluetooth_status="Bluetooth Pairing ...";
    delay(1);

    if (serialBT.available())
    { 
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

    }
    

  }

// ============== OLED Screen ================

}
void OLEDScreenDisplay(void *pvParameters)
{
  long currentMillisOLED= 0;
  long previousMillisOLED= 0;
  OLED.Clear();
  OLED.Display();
  delay(1000);
  while (1)
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
    delay(1);
  }
 
}
void BatteryVoltage(void *pvParameters)
{
  long currentMillisBatteryVoltage= 0;
  long previousMillisBatteryVoltage = 0;
  float Battery_Voltage = 0.0;
  int r1 = 33000;
  int r2 = 21000;
  float Calibration_Resistor = 1.14;
  while (1)
  {
    currentMillisBatteryVoltage = millis();
    if (currentMillisBatteryVoltage - previousMillisBatteryVoltage > 500){
      // Battery_Voltage = map(analogRead(33), 0.0f, 4095.0f, 0, 3.3);
      Battery_Voltage = analogRead(33);
      Serial.print("Battery analog: ");
      Serial.println(Battery_Voltage);
      Battery_Voltage = map(Battery_Voltage, 0.0f, 4095.0f, 0, 3300);
      Battery_Voltage = Battery_Voltage/1000;
      Battery_Voltage = Battery_Voltage/2*(r1+r2)/r2*Calibration_Resistor;
      snprintf(Battery_OLED_MESSAGE,
        255,
        PSTR("Batt: %0.2fV"),
        Battery_Voltage
      );
      float batteryLevel = map(analogRead(33), 0.0f, 4095.0f, 0, 100);
      previousMillisBatteryVoltage = millis();
    }
    delay(1);
  }
 
}


// ================= SETUP ====================
void setup() {
  Serial.begin(115200);
  Serial.println("======= SETUP =======");

  delay(50);
  // -------------- OLED --------------
  OLED.setup();
  xTaskCreatePinnedToCore(OLEDScreenDisplay, "OLEDScreenDisplay", 5000, NULL, 9, NULL, 1);

  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 8);
  // // Display static text
  // display.println("Initializing ...");
  // display.display(); 
// ---------------------------------------
  delay(3000);
  DEBUG_OLED_MESSAGE = "Start Bluetooth";
  delay(500);
  BLC.setup();
  delay(1000);

  DEBUG_OLED_MESSAGE = "Start pH";
  delay(500);
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
  delay(2000);

  Init_OK = true;
  DEBUG_OLED_MESSAGE = "All OK";

  // [DEBUG] Delete File
  Data_S.deleteFile(SPIFFS,"/2022-12_data.csv");

  Serial.println("=====================");




  xTaskCreatePinnedToCore(DataReading, "DataReading", 16000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(BTConnect, "BTConnect", 5000, NULL, 9, NULL, 1);
  xTaskCreatePinnedToCore(BatteryVoltage, "BatteryVoltage", 5000, NULL, 10, NULL, 1);

}



// ================= LOOP ======================
void loop() {


}
