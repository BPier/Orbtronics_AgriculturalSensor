#include "Arduino.h"
#include "OLED_Display.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Time_lib.h"

Timelib Time_OLED;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

bool OLED_Connected=false;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


OLEDDisplay::OLEDDisplay(int powerpin)
{
  pinMode(powerpin, OUTPUT);
  _powerpin = powerpin;

  return;
}

void OLEDDisplay::setup()
{
  digitalWrite(_powerpin,HIGH);
  delay(500);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    // for(;;);
  } else {
    OLED_Connected=true;
  }
  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);

  return;
}

void OLEDDisplay::WriteLine(const char* Text, int line){
  if(OLED_Connected){
    int cursorX=0;
    int cursorY=line*8;
    display.setCursor(cursorX, cursorY);
    display.println(Text);
  }


}

void OLEDDisplay::Clear(){
  if(OLED_Connected){
    display.clearDisplay();
  }
}

void OLEDDisplay::Display(){
  if(OLED_Connected){
    display.display();
  }
}

void OLEDDisplay::CurrentValues(const float pH, const int Moisture, const float Temp){
  char CharText[50];
  if(OLED_Connected){
    // Clear();
    String Formated_time = Time_OLED.FormatTime();
    char time[50];
    Formated_time.toCharArray(time,50);
    WriteLine(time,1);
    sprintf(CharText,"Temperature: %.1fC",Temp);
    WriteLine(CharText,2);
    sprintf(CharText,"pH: %.1f",pH);
    WriteLine(CharText,3);
    sprintf(CharText,"Moisture: %d%%%",Moisture);
    WriteLine(CharText,4);
    // Display();
  }
}


