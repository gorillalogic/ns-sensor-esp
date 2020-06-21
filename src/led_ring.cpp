#include "led_ring.h"

void LedRing::setup(){
  strip->begin();
  strip->setBrightness(20);
}

void LedRing::clear(){
  strip->clear();
}

uint16_t LedRing::getTotalLeds(){
  return totalLeds;
}

uint16_t LedRing::getPinVIN(){
  return pinVIN;
}

Adafruit_NeoPixel* LedRing::getStrip(){
  return strip;
}

LedRing::LedRing(uint16_t totalLeds, uint16_t pinVIN){
  this->totalLeds = totalLeds;
  this->pinVIN = pinVIN;
  strip = new Adafruit_NeoPixel(totalLeds, pinVIN, NEO_GRB + NEO_KHZ800);
}

LedRing::~LedRing(){
  free(strip);
}
