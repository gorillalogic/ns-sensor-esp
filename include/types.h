#pragma once

#include <Arduino.h>

typedef struct WifiCredentials {
  const char *ssid;
  const char *pass;
} WifiCredentials;

typedef struct Hostname {
  const char *name;
  const char *domain;
} Hostname;

typedef struct MqttCredentials {
  const char *username;
  const char *password;
} MqttCredentials;

typedef struct MqttConfig {
  Hostname hostname;
  uint16_t port;
} MqttConfig;

typedef struct SensorPayload {
  const uint16_t min;
  const uint16_t max;
  const uint16_t avg;
  const char* deviceId;
} SensorPayload;
