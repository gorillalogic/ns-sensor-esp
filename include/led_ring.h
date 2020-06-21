#pragma once

#include <Adafruit_NeoPixel.h>

class LedRing{
  private:
    Adafruit_NeoPixel* strip;
    uint16_t totalLeds;
    uint16_t pinVIN;

  public:
    explicit LedRing(uint16_t totalLeds, uint16_t pinVIN);
    ~LedRing();

    void setup();
    void clear();
    uint16_t getTotalLeds();
    uint16_t getPinVIN();
    Adafruit_NeoPixel* getStrip();
};
