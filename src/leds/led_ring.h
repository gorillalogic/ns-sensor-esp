#ifndef LED_RING_H
#define LED_RING_H

#include <Adafruit_NeoPixel.h>

class LedRing{
  private:
    Adafruit_NeoPixel strip;
    int totalLeds;
    int pinVIN;

  public:
    explicit LedRing(int totalLeds, int pinVIN);
    ~LedRing();

    void setup();
    void clear();
    int getTotalLeds();
    int getPinVIN();
    Adafruit_NeoPixel &getStrip();
};

#endif /* LED_RING_H */