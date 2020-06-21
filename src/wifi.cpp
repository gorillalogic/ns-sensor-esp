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
  Log.notice("SSID: %s", WiFi.SSID().c_str());
  Log.notice("IP address: %s", WiFi.localIP().toString().c_str());
}

void Wifi::disconnect(){

}

Wifi::Wifi(std::vector<WifiCredentials> credentials){
  wifiMulti = ESP8266WiFiMulti();

  std::vector<WifiCredentials>::iterator it = credentials.begin();
  for (std::vector<WifiCredentials>::iterator it = credentials.begin() ; it != credentials.end(); ++it){
    WifiCredentials cred = *it;
    wifiMulti.addAP(cred.ssid, cred.pass);
  }
}

Wifi::~Wifi(){

}
