#pragma once

#include "sensor.h"

class DigitalSensor : public Sensor{
  protected:
    int read();

  public:
    DigitalSensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt);
};
