#pragma once

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

typedef ESP8266WiFiMulti WiFiMultiController;
#endif

#if defined(ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>

typedef WiFiMulti WiFiMultiController;
#endif

#include "config.h"

class NS_WiFi{
  private:
    WiFiMultiController wifiMulti;
    std::string ipAddress;

  public:
    explicit NS_WiFi(std::vector<WifiCredentials> credentials);
    ~NS_WiFi();

    bool isConnected();
    std::string currentIpAddress();
    void connect();
    void disconnect();
};
