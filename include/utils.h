#pragma once

#include "types.h"

class Utils{
  public:
    static uint16_t calculateLeds(uint16_t noiseMeasurement, uint16_t minMeasurement, uint16_t maxMeasurement, uint16_t steps);
};
