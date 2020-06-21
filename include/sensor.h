#pragma once

#include "types.h"
#include "sampling.h"
#include "mqtt.h"

/**
 * Abstract class declaration.
 * Check DigitalSensor and AnalogSensor subclasses.
 */
class Sensor{
  private:
    const char * const id;
    Sampling sampling;
    Mqtt *mqtt;

  protected:
    const uint8_t inputPin;
    virtual int read();

  public:
    explicit Sensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt);
    ~Sensor();

    uint16_t nextCycle();
};
