#include "utils.h"

uint16_t Utils::calculateLeds(uint16_t noiseMeasurement, uint16_t minMeasurement, uint16_t maxMeasurement, uint16_t maxSteps){
  uint16_t steps;
  if (noiseMeasurement > maxMeasurement){
    steps = maxSteps;
  }else if (noiseMeasurement < minMeasurement){
    steps = 0;
  }else{
    steps = maxSteps * (noiseMeasurement - minMeasurement) / (maxMeasurement - minMeasurement);
  }
  return steps;
}
