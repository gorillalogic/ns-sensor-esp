#include "mqtt.h"

void Mqtt::publish(){
  char event[100];
  sprintf(event, "%s %d %d %d", device.c_str(), noiseAvg(), noise_max, noise_min);
  if (!noiseFeed.publish(event)){
    if (mqttFailures >= 10){
      mqttClient.disconnect();
      connect();
      mqttFailures = 0;
      return;
    }
    Serial.println(log::mqtt::failedSending);
    mqttFailures += 1;
  }
}

bool Mqtt::isConnected(){

}

void Mqtt::connect(){
if (mqttClient.connected()) {
    return;
  }
  int8_t ret;
  Serial.print(log::mqtt::connecting);
  uint8_t retries = 3;
  while ((ret = mqttClient.connect()) != 0) { // connect will return 0 for connected

    Serial.println(mqttClient.connectErrorString(ret));
    Serial.println(log::mqtt::retrying);

    mqttClient.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println(log::mqtt::connected);
}

void Mqtt::disconnect(){

}

Mqtt::Mqtt(string deviceId, Hostname server, Config config, Credentials credentials, const char *channel){
  wifiClient = WiFiClient();
  mqttClient = Adafruit_MQTT_Client(
    &wifiClient,
    config.server,
    config.port,
    credentials.username,
    credentials.password
  );
  feed = Adafruit_MQTT_Publish(&mqtt, channel);
  mqttFailures = 0;
  this->device = device;
}

Mqtt::~Mqtt(){

}