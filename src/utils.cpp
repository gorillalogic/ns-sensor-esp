#include "utils.h"

int Utils::calculateLeds(int noiseMeasurement, int minMeasurement, int maxMeasurement, int maxSteps){
  int steps;
  if (noiseMeasurement > maxMeasurement){
    steps = maxSteps;
  }else if (noiseMeasurement < minMeasurement){
    steps = 0;
  }else{
    steps = maxSteps * (noiseMeasurement - minMeasurement) / (maxMeasurement - minMeasurement);
  }
  return steps;
}
