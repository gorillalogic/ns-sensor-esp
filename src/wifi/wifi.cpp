#include "wifi.h"
#include "log.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

bool Wifi::isConnected(){

}

string Wifi::currentIpAddress(){
  return ipAddress;
}

void Wifi::connect(){
  Serial.println(log::wifi::connecting);
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print(log::wifi::connected);
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
