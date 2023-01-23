#include <npk_and_ph.h>
#include <Arduino.h>

#define RE  2
#define DE  0
 
//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xE4, 0x0C};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte pH[] = {0x01,0x03, 0x00, 0x0d, 0x00, 0x01, 0x15, 0xC9};

byte values[11];
SoftwareSerial mod(14,12);


// byte nitrogen()
// {
//     digitalWrite(DE, HIGH);
//     digitalWrite(RE, HIGH);
//     delay(10);
//     if(mod.write(nitro,sizeof(nitro))==8){
//         digitalWrite(DE,LOW);
//         digitalWrite(RE,LOW);
//         for(byte i=0;i<7;i++){
//             values[i] = mod.read();
//             Serial.print(values[i]);
//             Serial.print(" ");
//         }
//         Serial.print(values[4]);
//         return values[4];
//     }
    // if(mod.write(phos,sizeof(phos))==8){
    //     digitalWrite(DE,LOW);
    //     digitalWrite(RE,LOW);
    //     for(byte i=0;i<7;i++){
    //         values[i] = mod.read();
    //         Serial.print(values[i]);
    //         Serial.print(" ");
    //     }
    //     Serial.print(values[4]);
    //     return values[4]
    // }
    // if(mod.write(pota,sizeof(pota))==8){
    //     digitalWrite(DE,LOW);
    //     digitalWrite(RE,LOW);
    //     for(byte i=0;i<7;i++){
    //         values[i] = mod.read();
    //         Serial.print(values[i]);
    //         Serial.print(" ");
    //     }
    //     Serial.print(values[4]);
    //     return values[4]
    // }
    //  if(mod.write(pH,sizeof(pH))==8){
    //     digitalWrite(DE,LOW);
    //     digitalWrite(RE,LOW);
    //     for(byte i=0;i<7;i++){
    //         values[i] = mod.read();
    //         Serial.print(values[i]);
    //         Serial.print(" ");
    //     }
    //     Serial.print(values[4]);
    //     return values[4]
    // }



// }



 byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(100);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    // Serial.print("N: ");
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    //   Serial.print(values[i]);
    //   Serial.print(" ");
     }
    Serial.println();
  }
  Serial.println(values[4]);
  return values[4];
}
 
// byte phosphorous(){
//   digitalWrite(DE,HIGH);
//   digitalWrite(RE,HIGH);
//   delay(100);
//   if(mod.write(phos,sizeof(phos))==8){
//     digitalWrite(DE,LOW);
//     digitalWrite(RE,LOW);
//     // Serial.print("P: ");
//     for(byte i=0;i<7;i++){
//       values[i] = mod.read();
//     //   Serial.print(values[i]);
//     //   Serial.print(" ");
//     }
//     Serial.println();
//   }
//   return values[4];
// }
 
// byte potassium(){
//   digitalWrite(DE,HIGH);
//   digitalWrite(RE,HIGH);
//   delay(100);
//   if(mod.write(pota,sizeof(pota))==8){
//     digitalWrite(DE,LOW);
//     digitalWrite(RE,LOW);
//     // Serial.print("K: ");
//     for(byte i=0;i<7;i++){
//       values[i] = mod.read();
//     //   Serial.print(values[i]);
//     //   Serial.print(" ");
//     }
//     Serial.println();
//   }
//   return values[4];
// }

//  byte pH_value(){
//   digitalWrite(DE,HIGH);
//   digitalWrite(RE,HIGH);
//   delay(100);
//   if(mod.write(pH,sizeof(pH))==8){
//     digitalWrite(DE,LOW);
//     digitalWrite(RE,LOW);
//     // Serial.print("pH: ");
//     for(byte i=0;i<7;i++){
//       values[i] = mod.read();
//     //   Serial.print(values[i]);
//     //   Serial.print(" ");
//      }
//     Serial.println();
//   }
//   return values[4];
// }
 
npk_and_ph::npk_and_ph(){
  return;
}

void npk_and_ph::setup()
{
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

}

int npk_and_ph::Nitrogen()
{
    byte val1;
    delay(250);
    val1 = nitrogen();
    return val1;
}

// int npk_and_ph::Phosphorus()
// {
//     byte val2;
//     delay(250);
//     val2 = phosphorous();
//     return val2;
// }

// int npk_and_ph::Potassium()
// {
//     byte val3;
//     delay(250);
//     val3 = potassium();
//     return val3;
// }

// int npk_and_ph:: pH()
// {
//     float val4;
//     delay(250);
//     val4 = float(pH_value())/10;
//     return val4;
// }

// int npk_and_ph::test()
// {
//     byte val1;
//     delay(250);
//     val1 = test();
//     return val1;
// }
