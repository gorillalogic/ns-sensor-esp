#pragma once

#include "types.h"

class Sampling{
  private:
    const char * const signalName;
    uint16_t limit;
    uint16_t max;
    uint16_t min;
    uint16_t iteration;
    uint32_t sum;

  public:
    explicit Sampling(const char * const signalName, const uint16_t limit);
    ~Sampling();

    void add(uint16_t value);
    bool enoughSamples();
    SensorPayload read();
    void clear();
};
