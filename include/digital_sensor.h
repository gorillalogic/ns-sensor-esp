#pragma once

#include "sensor.h"

class DigitalSensor : public Sensor{
  protected:
    int read();

  public:
    DigitalSensor(const char * const id, const uint8_t inputPin, NS_MQTT *mqtt, const uint8_t controlPin);
};
