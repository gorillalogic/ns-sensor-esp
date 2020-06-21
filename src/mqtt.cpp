#include "mqtt.h"
#include "logger.h"

void Mqtt::publish(SensorPayload payload){
  char event[100];
  sprintf(event, "%s %d %d %d", payload.deviceId, payload.avg, payload.max, payload.min);
  if (!feed->publish(event)){
    if (mqttFailures >= 10){
      mqttClient->disconnect();
      connect();
      mqttFailures = 0;
      return;
    }
    Log.error(logger::mqtt::failedSending);
    mqttFailures += 1;
  }
}

bool Mqtt::isConnected(){
  return false;
}

void Mqtt::connect(){
if (mqttClient->connected()) {
    return;
  }
  int8_t ret;
  Log.notice(logger::mqtt::connecting);
  uint8_t retries = 3;
  while ((ret = mqttClient->connect()) != 0) { // connect will return 0 for connected

    Log.error(mqttClient->connectErrorString(ret));
    Log.notice(logger::mqtt::retrying);

    mqttClient->disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Log.notice(logger::mqtt::connected);
}

void Mqtt::disconnect(){

}

Mqtt::Mqtt(MqttConfig config, MqttCredentials credentials, const char *channel){
  wifiClient = new WiFiClient();
  mqttClient = new Adafruit_MQTT_Client(
    wifiClient,
    config.hostname.domain,
    config.port,
    credentials.username,
    credentials.password
  );
  feed = new Adafruit_MQTT_Publish(mqttClient, channel);
  mqttFailures = 0;
}

Mqtt::~Mqtt(){

}