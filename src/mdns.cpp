#include "mdns.h"
#include "config.h"
#include "logger.h"

#if defined(ESP8266)
#include <ESP8266mDNS.h>
#endif

#if defined(ESP32)
#include <WiFi.h>
#include <mdns.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#endif

void Mdns::assign(){
  if (!MDNS.begin(config::mdns::HOSTNAME.name)) {
    Log.error(logger::mdns::setupError);
  }
  Log.notice(logger::mdns::responderStarted);
}

bool Mdns::clear(){
  return false;
}

void Mdns::update(){
#if defined(ESP8266)
  MDNS.update();
#endif
}

void Mdns::start(){
  if ( MDNS.begin(config::mdns::HOSTNAME.name) ){
    Log.notice(logger::mdns::started);
  }
  MDNS.addService("http", "tcp", 80);
}

Mdns::Mdns(){}
Mdns::~Mdns(){}