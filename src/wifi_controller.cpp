#include "wifi_controller.h"
#include "logger.h"

bool WifiController::isConnected(){
  return false;
}

std::string WifiController::currentIpAddress(){
  return ipAddress;
}

void WifiController::connect(){
  Log.notice(logger::wifi::connecting);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
  }
  Log.notice(logger::wifi::connected);
  Log.notice(logger::wifi::ssid, WiFi.SSID().c_str());
  Log.notice(logger::wifi::ip, WiFi.localIP().toString().c_str());
}

void WifiController::disconnect(){

}

WifiController::WifiController(std::vector<WifiCredentials> credentials){
  wifiMulti = WiFiMultiController();

  std::vector<WifiCredentials>::iterator it = credentials.begin();
  for (std::vector<WifiCredentials>::iterator it = credentials.begin() ; it != credentials.end(); ++it){
    WifiCredentials cred = *it;
    wifiMulti.addAP(cred.ssid, cred.pass);
    Log.notice(logger::wifi::addingCredentials, cred.ssid, cred.pass);
  }
}

WifiController::~WifiController(){}
