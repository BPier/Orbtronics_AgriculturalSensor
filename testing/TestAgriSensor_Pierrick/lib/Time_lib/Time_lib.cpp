#include "Arduino.h"
#include "Time_lib.h"

Timelib::Timelib()
{

}

void Timelib::setup()
{
  Serial.print("[INFO] : The Time is Set up ");
}


unsigned long Timelib::GetTime()
{
  unsigned long Timems = millis();
  // Serial.print("[INFO] - Time is ");
  // Serial.print(Timems);
  // Serial.println("ms");

  return millis();

}

char* Timelib::FormatTime(unsigned long timemillis)
{
    unsigned long seconds, sec, min, hrs;
    static char FormatedT[30];
    // Convert milliseconds to seconds
    seconds = timemillis / 1000;

    // Get Hours, min, seconds from the milliseconds
    sec = seconds % 60;
    seconds /= 60;
    min = seconds % 60;    
    seconds /= 60;
    hrs = seconds % 24;

    snprintf(FormatedT,
      30,
      PSTR("%02d:%02d:%02d"),
      hrs,
      min,
      sec
    );
    // Serial.printf("%02d:%02d:%02d\n", hrs, min, sec);
    // Serial.print("[DEBUG] - FormatedT in Timelib::FormatTime is equal to ");Serial.println(FormatedT);
    return FormatedT;
}


