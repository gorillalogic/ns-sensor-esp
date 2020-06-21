#include "LedRing.h"

LedRing::LedRing(int totalLeds, int pinVIN){
  this->totalLeds = totalLeds;
  this->pinVIN = pinVIN;
  strip = Adafruit_NeoPixel(totalLeds, pinVIN, NEO_GRB + NEO_KHZ800);
}

LedRing::~LedRing(){

}

void LedRing::setup(){
  strip.begin();
  strip.setBrightness(20);
}

void LedRing::clear(){

}

int LedRing::totalLeds(){
  return totalLeds;
}

int LedRing::getPinVIN(){
  return pinVIN;
}

Adafruit_NeoPixel &LedRing::getStrip(){
  return strip;
}