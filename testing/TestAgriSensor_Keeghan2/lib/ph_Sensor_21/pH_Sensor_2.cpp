#include <pH_Sensor_2.h>
#include <NPK_Sensor.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define RE  2
#define DE  0
 
//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte pH[] = {0x01,0x03, 0x00, 0x0d, 0x00, 0x01, 0x15, 0xC9};

byte values[11];
// SoftwareSerial mod(14,12);

 byte pH_value(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pH,sizeof(pH))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
     }
    Serial.println();
  }
  return values[4];
}
 

pHSensor::pHSensor(){
  return;
}

void pHSensor::setup()
{
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

}

int pHSensor::pH()
{
    float val1;
    delay(250);
    val1 = float(pH_value())/10;
    return val1;
}
