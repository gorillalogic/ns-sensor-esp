#ifndef TRANSFORMS_H
#define TRANSFORMS_H

class Transforms{
  public:
    explicit Transforms();

    static int discreteSteps(int noiseMeasurement, int minMeasurement, int maxMeasurement, int steps);
};

#endif /* TRANSFORMS_H */