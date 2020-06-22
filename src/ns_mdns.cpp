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

const char * NS_mDNS::queryCollectorHost(){
#if defined(ESP8266)
  return config::mdns::COLLECTOR.domain;
#endif
#if defined(ESP32)
  const char *query = config::mdns::COLLECTOR.name;
  const char *result = MDNS.queryHost(query).toString().c_str();
  Log.notice("mDNS Query: (%s) Found: (%s)" CR, query, result);
  return result;
#endif
}

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

NS_mDNS::NS_mDNS(){}
NS_mDNS::~NS_mDNS(){}