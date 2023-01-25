#include <BluetoothSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <BluetoothConnectivity.h>
#include <esp_bt.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;

BluetoothConnectivity::BluetoothConnectivity(int switchPin, int LEDPin)
{
    pinMode(switchPin, INPUT);
    _switchPin= switchPin;
    pinMode(LEDPin, OUTPUT);
    _LEDPin = LEDPin;
    return;
}

void BluetoothConnectivity::setup()
{
    SerialBT.begin("CropMate"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
    digitalWrite(_LEDPin,HIGH);

}

void BluetoothConnectivity::BT_Write()
{
    
    if (Serial.available()) {
        SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
        Serial.write(SerialBT.read());
    }

  delay(20);
}

void BluetoothConnectivity::stop()
{
    SerialBT.end();
    // esp_bt_controller_disable();
    // esp_bluedroid_disable();
    digitalWrite(_LEDPin,LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);  

}