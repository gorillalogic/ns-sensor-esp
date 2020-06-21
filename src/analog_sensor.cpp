#include "analog_sensor.h"

int AnalogSensor::read(){
  return analogRead(this->inputPin);
}

AnalogSensor::AnalogSensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt) :
    Sensor(id, inputPin, mqtt){};
