#include <NPK_Sensor.h>
#include <Arduino.h>

#define RE  2
#define DE  0
 
//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xE4, 0x0C};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
SoftwareSerial mod(14,27);

 byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
     }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
    Serial.println();
  }
  return values[4];
}


NPKSensor::NPKSensor(){
  return;
}

void NPKSensor::setup()
{
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

}

int NPKSensor::Nitrogen()
{
    byte val1;
    delay(250);
    val1 = nitrogen();
    return val1;
}

int NPKSensor::Phosphorus()
{
    byte val2;
    delay(250);
    val2 = phosphorous();
    return val2;
}

int NPKSensor::Potassium()
{
    byte val3;
    delay(250);
    val3 = potassium();
    return val3;
}