#include "ns_mdns.h"
#include "config.h"
#include "logger.h"
#include <IPAddress.h>

#if defined(ESP8266)
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#endif

#if defined(ESP32)
#include <mdns.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#endif

void NS_mDNS::queryCollectorHost(IPAddress &result){
#if defined(ESP8266)
  query = config::mdns::COLLECTOR.domain;
  WiFi.hostByName(query, result);
  Log.notice("mDNS Query: (%s) Found: (%s)" CR, query, result.toString().c_str());
#endif
#if defined(ESP32)
  query = config::mdns::COLLECTOR.name;
  IPAddress host = MDNS.queryHost(query);
  result.fromString(host.toString());
  Log.notice("mDNS Query: (%s) Found: (%s)" CR, query, result.toString().c_str());
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