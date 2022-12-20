#include <Arduino.h>
#define LED 33
#define Button 35

void morse_dash();
void morse_dot();

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(Button,INPUT);
  Serial.begin(115200);
}

void loop() {
  // if (ButtonStatus){
  //   digitalWrite(LED,HIGH);
  // }
  // else {
  //   digitalWrite(LED,LOW);
  // }
  // if (ButtonStatus == 0){
  //   ButtonStatus = digitalRead(Button);
  //   if (ButtonStatus == 1){
  //     LEDState = !LEDState;
  //   }
  // }
  // if (LEDState == 1){
  //   digitalWrite(LED,HIGH);
  // }
  // else {
  //   digitalWrite(LED,LOW);
  // }

  // ButtonStatus = digitalRead(Button);
  morse_dot();
  morse_dot();
  morse_dash();

}

void morse_dash() {
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
}

void morse_dot() {
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(LED,LOW);
}