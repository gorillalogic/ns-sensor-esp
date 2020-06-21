#include "mdns.h"
#include "../../config.h"
#include "../../log.h"
#include <ESP8266mDNS.h>

void MDns::assign(){
  if (!MDNS.begin(config::mdns::LOCAL.name)) {             // Start the mDNS responder for esp8266.local
    Serial.println(log::mdns::setupError);
  }
  Serial.println(log::mdns::responderStarted);
}

bool MDns::clear(){

}

void MDns::update(){
  MDNS.update();
}

void MDns::start(){
  if ( MDNS.begin(config::mdns::LOCAL.name) ){
    Serial.println(log::mdns::started);
  }
  MDNS.addService("http", "tcp", 80);
}

MDns::MDns(){

}

MDns::~MDns(){

}