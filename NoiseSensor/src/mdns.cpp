#include "mdns.h"
#include "config/config.h"
#include "config/logger.h"
#include <ESP8266mDNS.h>

void Mdns::assign(){
  if (!MDNS.begin(config::mdns::HOSTNAME.name)) {             // Start the mDNS responder for esp8266.local
    Serial.println(logger::mdns::setupError);
  }
  Serial.println(logger::mdns::responderStarted);
}

bool Mdns::clear(){
  return false;
}

void Mdns::update(){
  MDNS.update();
}

void Mdns::start(){
  if ( MDNS.begin(config::mdns::HOSTNAME.name) ){
    Serial.println(logger::mdns::started);
  }
  MDNS.addService("http", "tcp", 80);
}

Mdns::Mdns(){

}

Mdns::~Mdns(){

}