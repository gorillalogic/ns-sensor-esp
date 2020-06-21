#include "analog_sensor.h"

int AnalogSensor::read(){
  return analogRead(this->inputPin);
}

AnalogSensor::AnalogSensor(const char * const id, const uint8_t inputPin, NS_MQTT *mqtt, const uint8_t controlPin) :
    Sensor(id, inputPin, mqtt, controlPin){};
