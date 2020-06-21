#pragma once

#include "types.h"

class Sampling{
  private:
    const char *deviceId;
    int limit;
    int max;
    int min;
    int sum;
    int iteration;

  public:
    explicit Sampling(const int limit, const char *deviceId);
    ~Sampling();

    void add(int value);
    bool enoughSamples();
    SensorPayload read();
    void clear();
};
