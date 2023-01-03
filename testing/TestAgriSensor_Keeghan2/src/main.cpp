#include <Arduino.h>
#include <BluetoothConnectivity.h>
#include <BluetoothSerial.h>
#include <SPI.h>

BluetoothConnectivity BLC;
BluetoothSerial serialBT;

void setup()
{
  Serial.begin(115200);
  BLC.setup();
}

void loop()
{
  BLC.BT_Write();
  serialBT.println("hello");
  delay(1000);
}

