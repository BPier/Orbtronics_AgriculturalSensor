#include <Arduino.h>
#include <Time_lib.h>
#include <SPI.h>
#include <RTClib.h>

RTC_DS1307 rtc;
bool RTC_Connected = false;

Timelib::Timelib()
{

}

void Timelib::setup()
{
  // Serial.begin(115200);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("[ERROR] Couldn't find RTC");
    Serial.flush();
    // while (1) delay(10);
    RTC_Connected = false;
  } else {
    RTC_Connected = true;
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2023, 1, 25, 13, 30, 0));
}


String Timelib::FormatTime()
{
  String str_time;
  if (RTC_Connected) {
    DateTime time = rtc.now();
    str_time = time.timestamp(DateTime::TIMESTAMP_FULL);
  } else {
    str_time = "1970-01-01T00:00:00";
  }
  //Full Timestamp

  return str_time;

}

DateTime Timelib::GetTime()
{

  DateTime time = rtc.now();

  return time;
}

