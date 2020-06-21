#pragma once

#include "types.h"
#include "sampling.h"
#include "ns_mqtt.h"

/**
 * Abstract class declaration.
 * Check DigitalSensor and AnalogSensor subclasses.
 */
class Sensor{
  private:
    const char * const id;
    Sampling sampling;
    NS_MQTT *mqtt;

  protected:
    const uint8_t inputPin;
    const uint8_t controlPin;
    virtual int read();

  public:
    explicit Sensor(const char * const id, const uint8_t inputPin, NS_MQTT *mqtt, const uint8_t controlPin);
    void enable();
    void disable();
    ~Sensor();

    uint16_t nextCycle();
};
