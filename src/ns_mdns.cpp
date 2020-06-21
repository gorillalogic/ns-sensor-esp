#include "ns_mdns.h"
#include "config.h"
#include "logger.h"

#if defined(ESP8266)
#include <ESP8266mDNS.h>
#endif

#if defined(ESP32)
#include <mdns.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#endif

void NS_mDNS::assign(){
  if (!MDNS.begin(config::mdns::HOSTNAME.name)) {
    Log.error(logger::mdns::setupError);
  }
  Log.notice(logger::mdns::responderStarted);
}

bool NS_mDNS::clear(){
  return false;
}

void NS_mDNS::update(){
#if defined(ESP8266)
  MDNS.update();
#endif
}

void NS_mDNS::start(){
  if ( MDNS.begin(config::mdns::HOSTNAME.name) ){
    Log.notice(logger::mdns::started);
  }
  MDNS.addService("http", "tcp", 80);
}

NS_mDNS::NS_mDNS(){}
NS_mDNS::~NS_mDNS(){}