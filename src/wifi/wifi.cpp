#include "wifi.h"
#include "../../strings.h"

bool Wifi::isConnected(){

}

std::string Wifi::currentIpAddress(){
  return ipAddress;
}

void Wifi::connect(){
  Serial.println(logger::wifi::connecting);
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print(logger::wifi::connected);
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

}

void Wifi::disconnect(){

}

Wifi::Wifi(){
  wifiMulti = ESP8266WiFiMulti();
  wifiMulti.addAP("IoT", "42noisealert42");
  wifiMulti.addAP("iPhone-Emma", "@noise42@");
  wifiMulti.addAP("GorillaGuest", "gorillalogicguest");
}

Wifi::~Wifi(){

}
