#pragma once

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#if defined(ESP32)
#include <WiFi.h>
#endif

#include <PubSubClient.h>

#include "types.h"
#include "config.h"

#define MSG_BUF_SIZE 200

class NS_MQTT{
  private:
    WiFiClient &wifiClient;
    PubSubClient &client;
    uint8_t mqttFailures;
    MqttConfig config;
    const char * username;
    const char * password;
    const char * feed_channel;
    const char * client_id;
    IPAddress server_ip;
    uint16_t server_port;
    String mac_address;
    char * message;

  public:
    explicit NS_MQTT(WiFiClient &wifiClient, PubSubClient &client);
    ~NS_MQTT();

    void publish(SensorPayload payload);
    bool isConnected();
    void connect();
    void loop();
    void disconnect();
    void setServerIP(IPAddress &ip);
    void setMacAddress(String &mac_address);

  private:
    void buildMsg(SensorPayload payload, char * buf);
};
