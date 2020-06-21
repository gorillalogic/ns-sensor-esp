#include "wifi.h"
#include "logger.h"

bool Wifi::isConnected(){
  return false;
}

std::string Wifi::currentIpAddress(){
  return ipAddress;
}

void Wifi::connect(){
  Log.notice(logger::wifi::connecting);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
  }
  Log.notice(logger::wifi::connected);
  Log.notice(logger::wifi::ssid, WiFi.SSID().c_str());
  Log.notice(logger::wifi::ip, WiFi.localIP().toString().c_str());
}

void Wifi::disconnect(){

}

Wifi::Wifi(std::vector<WifiCredentials> credentials){
  wifiMulti = ESP8266WiFiMulti();

  std::vector<WifiCredentials>::iterator it = credentials.begin();
  for (std::vector<WifiCredentials>::iterator it = credentials.begin() ; it != credentials.end(); ++it){
    WifiCredentials cred = *it;
    wifiMulti.addAP(cred.ssid, cred.pass);
    Log.notice(logger::wifi::addingCredentials, cred.ssid, cred.pass);
  }
}

Wifi::~Wifi(){}
