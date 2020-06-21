#pragma once

#include "led_ring.h"

class Animations {
  private:
    uint32_t green;
    uint32_t red;
    uint32_t yellow;
    LedRing &ledRing;
    uint16_t high;
    uint16_t low;

  public:
    explicit Animations(LedRing &ledRing, double ratioLow, double ratioHigh);
    ~Animations();

    void clear();
    void noiseMagnitude(uint16_t steps);
};
