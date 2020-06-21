#include "analog_multiplexor.h"
#include "logger.h"

void AnalogMultiplexor::addAnalogSensor(AnalogSensor* sensor){
  Log.notice("Adding new analog sensor" CR);
  sensor->disable();
  sensors.push_back(sensor);
}

AnalogSensor* AnalogMultiplexor::sensorInTurn(){
  return *sensors.begin();
}

AnalogSensor* AnalogMultiplexor::rotate(){
  sensorInTurn()->disable();
  std::rotate(sensors.begin(), sensors.begin() + 1, sensors.end());
  sensorInTurn()->enable();
  return sensorInTurn();
}

AnalogMultiplexor::AnalogMultiplexor(){
  sensors = std::vector<AnalogSensor*>();
}

AnalogMultiplexor::~AnalogMultiplexor(){
  // TODO: finish!.
}