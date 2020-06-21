#include "mdns.h"
#include "config.h"
#include "logger.h"
#include <ESP8266mDNS.h>

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
  MDNS.update();
}

void Mdns::start(){
  if ( MDNS.begin(config::mdns::HOSTNAME.name) ){
    Log.notice(logger::mdns::started);
  }
  MDNS.addService("http", "tcp", 80);
}

Mdns::Mdns(){

}

Mdns::~Mdns(){

}