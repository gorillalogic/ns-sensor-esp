#include "sampling.h"
#include "logger.h"

void Sampling::add(int value){
  sum += value;
  if (value < min){
    min = value;
  }else if (value > max){
    max = value;
  }
  iteration += 1;
  Log.verbose("Sampling: Adding value: %d, min: %d, max: %d, sum: %d" CR, value, min, max, sum);
}

bool Sampling::enoughSamples(){
  return iteration % limit == 0;
}

SensorPayload Sampling::read(){
  SensorPayload payload = {
    min,
    max,
    sum / limit,
    deviceId,
  };
  Log.verbose("Sampling: Read deviceId: %s, min: %d, max: %d, avg: %d / %d = %d" CR,
    deviceId, min, max, sum, limit, sum / limit);
  return payload;
}

void Sampling::clear(){
  min = 10000;
  max = -1;
  sum = 0;
  iteration = 0;
}

Sampling::Sampling(const int limit, const char* deviceId){
  clear();
  this->limit = limit;
  this->deviceId = deviceId;
}

Sampling::~Sampling(){

}