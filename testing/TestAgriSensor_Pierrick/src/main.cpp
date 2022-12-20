#include <Arduino.h>
#include <Morse.h>

Morse morse(33);


void setup() {
    Serial.begin(115200);    
}

void loop() {
  morse.dot(); morse.dot(); morse.dot();
  morse.dash(); morse.dash(); morse.dash();
  morse.dot(); morse.dot(); morse.dot();
  delay(3000);
  morse.letter('a');
  delay(3000);
}