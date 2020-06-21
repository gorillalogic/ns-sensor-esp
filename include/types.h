#pragma once

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
  int port;
} MqttConfig;

typedef struct SensorPayload {
  const int min;
  const int max;
  const int avg;
  const char* deviceId;
} SensorPayload;
