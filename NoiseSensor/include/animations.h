#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Adafruit_NeoPixel.h>
#include "led_ring.h"

class Animations {
  private:
    uint32_t green;
    uint32_t red;
    uint32_t yellow;
    LedRing &ledRing;
    int high;
    int low;

  public:
    explicit Animations(LedRing &ledRing, double ratioLow, double ratioHigh);
    ~Animations();

    void clear();
    void noiseMagnitude(int steps);
};

#endif /* ANIMATIONS_H */
