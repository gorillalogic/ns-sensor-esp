#include "ns_mqtt.h"
#include "logger.h"

#define CONNECTED 0  // connect will return 0 for connected
#define LIMIT_FAILURES 10

void NS_MQTT::buildMsg(SensorPayload payload, char * buf){
  sprintf(buf, "%s %d %d %d %s", payload.signalName, payload.avg, payload.max,
    payload.min, mac_address.c_str());
}

void NS_MQTT::publish(SensorPayload payload){
  connect();
  memset(message, 0, MSG_BUF_SIZE);
  buildMsg(payload, message);
  Log.notice("MQTT: Payload: %s" CR, message);

  if (!client.publish(config::mqtt::channels::NOISE, message, true)){
    Log.error(logger::mqtt::failedSending);
  }else{
    Log.notice(logger::mqtt::payloadSent, message);
  }
}

bool NS_MQTT::isConnected(){
  return client.connected();
}

void NS_MQTT::connect(){
  if (this->isConnected()) {
    return;
  }

  do{
    client.connect(client_id, username, password);
    Log.notice("MQTT: STATE: %d" CR, client.state());
  } while(!client.connected());
  Log.notice(logger::mqtt::connected);
}

void NS_MQTT::disconnect(){

}

void NS_MQTT::loop(){
  client.loop();
}

void NS_MQTT::setServerIP(IPAddress &ip){
  this->server_ip = ip;
  this->client.setServer(ip, server_port);
}

void NS_MQTT::setMacAddress(String &mac_address){
  this->mac_address = mac_address;
}

void NS_MQTT::setClientId(String &deviceId){
  this->client_id = deviceId.c_str();
}

NS_MQTT::NS_MQTT(WiFiClient &wifiClient, PubSubClient &client):
    wifiClient(wifiClient), client(client){
  username = config::mqtt::DEFAULT_CREDENTIALS.username;
  password = config::mqtt::DEFAULT_CREDENTIALS.password;
  server_port = config::mqtt::DEFAULT_CONFIG.port;
  message = (char *) malloc(MSG_BUF_SIZE);
}

NS_MQTT::~NS_MQTT(){}
