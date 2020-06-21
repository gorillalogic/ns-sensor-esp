#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "types.h"
#include "config/config.h"

class Mqtt{
  private:
    WiFiClient *wifiClient;
    Adafruit_MQTT_Client *mqttClient;
    Adafruit_MQTT_Publish *feed;
    int mqttFailures;

  public:
    explicit Mqtt(MqttConfig config, MqttCredentials credentials, const char *channel);
    ~Mqtt();

    void publish(SensorPayload payload);
    bool isConnected();
    void connect();
    void disconnect();
};

#endif /* MQTT_H */