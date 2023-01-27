#ifndef myWifiOTA_h
#define myWifiOTA_h

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class myWifiOTA
{
  public:

    myWifiOTA();
    String setup(String SSID, String Password);
    void loop();
};

#endif