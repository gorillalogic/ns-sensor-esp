#pragma once

class Transforms{
  public:
    explicit Transforms();

    static int discreteSteps(int noiseMeasurement, int minMeasurement, int maxMeasurement, int steps);
};
