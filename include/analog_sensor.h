#pragma once

#include "sensor.h"

class AnalogSensor : public Sensor{
  protected:
    int read();

  public:
    AnalogSensor(const char * const id, const uint8_t inputPin, NS_MQTT *mqtt, const uint8_t controlPin);
};
