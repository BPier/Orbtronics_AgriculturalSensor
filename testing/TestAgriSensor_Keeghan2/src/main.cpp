#include <Arduino.h>
#include <BluetoothConnectivity.h>

BluetoothConnectivity BLC;

void setup()
{
  Serial.begin(115200);
  BLC.setup();
}

void loop()
{
  BLC.BT_Write();
}

