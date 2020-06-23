#include "sensor.h"
#include "config.h"

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

void Sensor::enable(){
  if (controlPin != config::pins::NO_CONTROL){
    digitalWrite(controlPin, 1); // 1 for ON
  }
}

void Sensor::disable(){
  if (controlPin != config::pins::NO_CONTROL){
    digitalWrite(controlPin, 0); // 0 for OFF
  }
}

Sensor::Sensor(const char * const id, const uint8_t inputPin, NS_MQTT *mqtt,
    const uint8_t controlPin = config::pins::NO_CONTROL) :
    id(id), sampling(id, config::sampling::AVERAGE_COUNT), mqtt(mqtt), inputPin(inputPin), controlPin(controlPin){};

Sensor::~Sensor(){
  free((void*)id);
  free(mqtt);
}
