#include "Arduino.h"

#include "Sleep.h"


Sleep::Sleep(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Sleep::PrintTime(unsigned long millisOffset)
{
    unsigned long seconds, sec, min, hrs;
    seconds = offsetMillis(millisOffset) / 1000;
    sec = seconds % 60;
    seconds /= 60;
    min = seconds % 60;    
    seconds /= 60;
    hrs = seconds % 24;
    Serial.printf("%02d:%02d:%02d\n", hrs, min, sec);
}

unsigned long Sleep::offsetMillis(unsigned long millisOffset)
{

}

