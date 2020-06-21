#include "digital_sensor.h"

int DigitalSensor::read(){
  return digitalRead(this->inputPin);
}

DigitalSensor::DigitalSensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt) :
    Sensor(id, inputPin, mqtt){};
