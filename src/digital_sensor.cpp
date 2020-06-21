#include "digital_sensor.h"
#include "config.h"

int DigitalSensor::read(){
  return digitalRead(this->inputPin);
}

DigitalSensor::DigitalSensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt,
   const uint8_t controlPin = config::pins::NO_CONTROL) : Sensor(id, inputPin, mqtt, controlPin){};
