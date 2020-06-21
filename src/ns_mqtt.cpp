#include "ns_mqtt.h"
#include "logger.h"

#define CONNECTED 0  // connect will return 0 for connected
#define LIMIT_FAILURES 10

void NS_MQTT::publish(SensorPayload payload){
  char event[100];
  sprintf(event, "%s %d %d %d %s", payload.signalName, payload.avg, payload.max, payload.min, macAddress.c_str());
  if (!feed->publish(event)){
    Log.error(logger::mqtt::failedSending);
    if (mqttFailures >= LIMIT_FAILURES){
      Log.error(logger::mqtt::failedSendingLimitTries, mqttFailures);
      mqttFailures = 0;
      mqttClient->disconnect();
      connect();
      return;
    }
    mqttFailures += 1;
  }else{
    Log.notice(logger::mqtt::payloadSent, payload.signalName, payload.avg, payload.max, payload.min, macAddress.c_str());
  }
}

bool NS_MQTT::isConnected(){
  return false;
}

void NS_MQTT::connect(){
  if (mqttClient->connected()) {
    return;
  }

  int8_t ret;
  uint8_t retries = 3;
  Log.notice(logger::mqtt::connecting);
  while ((ret = mqttClient->connect()) != CONNECTED) {
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

void NS_MQTT::disconnect(){

}

NS_MQTT::NS_MQTT(MqttConfig config, MqttCredentials credentials, const char *channel, String macAddress) :
    macAddress(macAddress){
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

NS_MQTT::~NS_MQTT(){
  delete wifiClient;
  delete mqttClient;
  delete feed;
}