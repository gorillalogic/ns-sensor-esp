#include "Animations.h"
#include "config.h"

void Animations::clear(){
  ledRing.clear();
}

void Animations::noiseMagnitude(int leds){
  clear();

  if (leds > high){
    ledRing.getStrip().fill(green, 0, low);
    ledRing.getStrip().fill(yellow, low, _high - low);
    ledRing.getStrip().fill(red, high, leds - high);
  }else if (leds > low){
    ledRing.getStrip().fill(green, 0, low);
    ledRing.getStrip().fill(yellow, low, leds - low);
  }else if (leds > 0){
    ledRing.getStrip().fill(green, 0, leds);
  }

  ledRing.getStrip().show();
}

Animations::Animations(LedRing &ledRing, double ratioLow, double ratioHigh){
  high = (int)(ledRing.getTotalLeds() * ratioHigh);
  low = (int)(ledRing.getTotalLeds() * ratioLow);

  green = strip.Color(0, 255, 0);
  yellow = strip.Color(255, 255, 0);
  red = strip.Color(255, 0, 0);
}