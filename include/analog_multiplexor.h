#pragma once

#include "analog_sensor.h"

class AnalogMultiplexor{
  private:
    std::vector<AnalogSensor*> sensors;

  public:
    explicit AnalogMultiplexor();
    ~AnalogMultiplexor();
    void addAnalogSensor(AnalogSensor* sensor);
    AnalogSensor* sensorInTurn();
    AnalogSensor* rotate();
};
