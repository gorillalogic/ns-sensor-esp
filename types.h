namespace wifi {
  typedef struct Credentials {
    const char *ssid;
    const char *pass;
  } Credentials;
}

namespace mdns {
  typedef struct Hostname {
    const char *name;
    const char *domainName;
  } Hostname;
}

namespace mqtt {
  typedef struct Credentials {
    const char *username;
    const char *password;
  } Credentials;

  typedef struct Config {
    int port;
    mdns::Hostname hostname;
  } Config;
}


typedef struct SensorPayload {
  const int min;
  const int max;
  const int avg;
  const char* deviceId;
} SensorPayload;