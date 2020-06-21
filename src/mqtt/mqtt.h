#include "config.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

using namespace std;
using namespace config::mqtt;

class Mqtt{
  private:
    WiFiClient wifiClient;
    Adafruit_MQTT_Client mqttClient;
    Adafruit_MQTT_Publish feed;
    string device;
    int mqttFailures;

  public:
    explicit Mqtt(string deviceId, Hostname server, Config config, Credentials credentials, const char *channel);
    ~Mqtt();

    void publish(SensorPayload payload);
    bool isConnected();
    void connect();
    void disconnect();
};
