#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "config.h"

class Wifi {
  private:
    ESP8266WiFiMulti wifiMulti;
    std::string ipAddress;

  public:
    explicit Wifi();
    ~Wifi();

    bool isConnected();
    std::string currentIpAddress();
    void connect();
    void disconnect();
};

#endif /* WIFI_H */