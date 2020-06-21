#include "sensor.h"

uint16_t Sensor::nextCycle(){
  uint16_t value = read();
  sampling.add(value);
  if (sampling.enoughSamples()){
    SensorPayload payload = sampling.read();
    mqtt->publish(payload);
    sampling.clear();
  }
  return value;
}

int Sensor::read(){
  return -1;
}

Sensor::Sensor(const char * const id, const uint8_t inputPin, Mqtt *mqtt) :
    id(id), sampling(id, config::sampling::AVERAGE_COUNT), mqtt(mqtt), inputPin(inputPin){};

Sensor::~Sensor(){
  free((void*)id);
  free(mqtt);
}
