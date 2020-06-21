#pragma once

class Utils{
  public:
    explicit Utils();

    int calculateLeds(int noiseMeasurement, int minMeasurement, int maxMeasurement, int steps);
};
