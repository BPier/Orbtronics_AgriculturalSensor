#include <Arduino.h>

#define LED 33
RTC_DATA_ATTR unsigned long millisOffset = 0;

unsigned long offsetMillis()
{
    return millis() + millisOffset;
}

#define uS_TO_mS_FACTOR 1000  /* Conversion factor for micro seconds to miliseconds */

void sleepSensor(unsigned long sleepMillis)
{
    esp_sleep_enable_timer_wakeup(sleepMillis * uS_TO_mS_FACTOR);
    millisOffset = offsetMillis() + sleepMillis;
    esp_deep_sleep_start();
}

void printTime()
{
    unsigned long seconds, sec, min, hrs;

    seconds = offsetMillis() / 1000;

    sec = seconds % 60;
    seconds /= 60;
    min = seconds % 60;    
    seconds /= 60;
    hrs = seconds % 24;

    Serial.printf("%02d:%02d:%02d\n", hrs, min, sec);
}


void setup() {
    Serial.begin(115200);
    pinMode(LED,OUTPUT);
    
}

void loop() {
  printTime();
  digitalWrite(LED,HIGH);
  delay(1000);
  sleepSensor(5000);
}