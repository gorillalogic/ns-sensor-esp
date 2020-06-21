#pragma once

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#if defined(ESP32)
#include <WiFi.h>
#endif

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "types.h"
#include "config.h"

class NS_MQTT{
  private:
    WiFiClient *wifiClient;
    Adafruit_MQTT_Client *mqttClient;
    Adafruit_MQTT_Publish *feed;
    uint8_t mqttFailures;
    String macAddress;

  public:
    explicit NS_MQTT(MqttConfig config, MqttCredentials credentials, const char *channel, String macAddress);
    ~NS_MQTT();

    void publish(SensorPayload payload);
    bool isConnected();
    void connect();
    void disconnect();
};
