#include "ns_wifi.h"
#include "logger.h"

bool NS_WiFi::isConnected(){
  return false;
}

std::string NS_WiFi::currentIpAddress(){
  return ipAddress;
}

void NS_WiFi::connect(){
  Log.notice(logger::wifi::connecting);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
  }
  Log.notice(logger::wifi::connected);
  Log.notice(logger::wifi::ssid, WiFi.SSID().c_str());
  Log.notice(logger::wifi::ip, WiFi.localIP().toString().c_str());
}

void NS_WiFi::disconnect(){

}

NS_WiFi::NS_WiFi(std::vector<WifiCredentials> credentials){
  wifiMulti = WiFiMultiController();

  std::vector<WifiCredentials>::iterator it = credentials.begin();
  for (std::vector<WifiCredentials>::iterator it = credentials.begin() ; it != credentials.end(); ++it){
    WifiCredentials cred = *it;
    wifiMulti.addAP(cred.ssid, cred.pass);
    Log.notice(logger::wifi::addingCredentials, cred.ssid, cred.pass);
  }
}

NS_WiFi::~NS_WiFi(){}
