#include <Arduino.h>
#define LED 33
#define Button 35
int ButtonStatus = 0;
int LEDState = 0;

void morse_dash(char dot_dash) {
}

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(Button,INPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.print("button Status:");
  Serial.println(ButtonStatus);
  // if (ButtonStatus){
  //   digitalWrite(LED,HIGH);
  // }
  // else {
  //   digitalWrite(LED,LOW);
  // }
  if (ButtonStatus == 0){
    ButtonStatus = digitalRead(Button);
    if (ButtonStatus == 1){
      LEDState = !LEDState;
    }
  }
  if (LEDState == 1){
    digitalWrite(LED,HIGH);
  }
  else {
    digitalWrite(LED,LOW);
  }

  ButtonStatus = digitalRead(Button);

}