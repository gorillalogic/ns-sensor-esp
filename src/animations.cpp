#include "animations.h"
#include "config.h"
#include "logger.h"

void Animations::clear(){
  ledRing.clear();
}

void Animations::noiseMagnitude(uint16 leds){
  ledRing.clear();
  Log.verbose("[noiseMagnitude] high:%d low:%d leds:%d" CR, high, low, leds);
  if (leds > high){
    Log.verbose("[noiseMagnitude] first" CR);
    ledRing.getStrip()->fill(green, 0, low);
    ledRing.getStrip()->fill(yellow, low, high - low);
    ledRing.getStrip()->fill(red, high, leds - high);
  }else if (leds > low){
    Log.verbose("[noiseMagnitude] second" CR);
    ledRing.getStrip()->fill(green, 0, low);
    ledRing.getStrip()->fill(yellow, low, leds - low);
  }else if (leds > 0){
    Log.verbose("[noiseMagnitude] third" CR);
    ledRing.getStrip()->fill(green, 0, leds);
  }

  ledRing.getStrip()->show();
}

Animations::Animations(LedRing &ledRing, double ratioLow, double ratioHigh) : ledRing(ledRing){
  high = (int)(ledRing.getTotalLeds() * ratioHigh);
  low = (int)(ledRing.getTotalLeds() * ratioLow);

  green = ledRing.getStrip()->Color(0, 255, 0);
  yellow = ledRing.getStrip()->Color(255, 255, 0);
  red = ledRing.getStrip()->Color(255, 0, 0);
}

Animations::~Animations(){

}
