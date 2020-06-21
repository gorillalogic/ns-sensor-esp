#include "sampling.h"
#include "logger.h"

void Sampling::add(uint16_t value){
  sum += value;
  if (value < min){
    min = value;
  }else if (value > max){
    max = value;
  }
  iteration += 1;
  Log.verbose(logger::sampling::addSampling, value, min, max, sum);
}

bool Sampling::enoughSamples(){
  return iteration % limit == 0;
}

SensorPayload Sampling::read(){
  uint16_t avg = sum / limit;
  SensorPayload payload = {
    min,
    max,
    avg,
    deviceId,
  };
  Log.verbose(logger::sampling::readSampling, deviceId, min, max, sum, limit, avg);
  return payload;
}

void Sampling::clear(){
  min = 0xFFFF;
  max = 0;
  sum = 0;
  iteration = 0;
}

Sampling::Sampling(const uint16_t limit, const char* deviceId){
  clear();
  this->limit = limit;
  this->deviceId = deviceId;
}

Sampling::~Sampling(){}