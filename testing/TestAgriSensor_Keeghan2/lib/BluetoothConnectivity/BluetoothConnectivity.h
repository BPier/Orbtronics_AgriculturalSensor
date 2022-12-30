#ifndef BluetoothConnectivity_h
#define BluetoothConnectivity_h

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

class BluetoothConnectivity
{
  public:
    BluetoothConnectivity();
    void setup();
    void BT_Write();
};

#endif