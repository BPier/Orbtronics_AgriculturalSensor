#include "Arduino.h"
#include "OLED_Display.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

bool Oled_Connected=false;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


OLEDDisplay::OLEDDisplay()
{

  return;
}

void OLEDDisplay::setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    // for(;;);
  } else {
    Oled_Connected=true;
  }
  return;
}

void OLEDDisplay::WriteLine(const char* Text, int line){
  int cursorX=0;
  int cursorY=line*8;
  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(cursorX, cursorY);
  display.println(Text);
  Display();

}

void OLEDDisplay::Clear(){
  display.clearDisplay();
}

void OLEDDisplay::Display(){
  display.display();
}

void OLEDDisplay::CurrentValues(const char* time, const float pH, const int Moisture, const float Temp){
  char CharText[50];
  Clear();
  WriteLine(time,1);
  sprintf(CharText,"Temperature: %.1fC",Temp);
  WriteLine(CharText,2);
  sprintf(CharText,"pH: %.1f",pH);
  WriteLine(CharText,3);
  sprintf(CharText,"Moisture: %d%%%",Moisture);
  WriteLine(CharText,4);
  Display();
}


