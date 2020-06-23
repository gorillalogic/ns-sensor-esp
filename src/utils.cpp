#include "utils.h"

uint16_t Utils::calculateLeds(uint16_t noiseMeasurement, uint16_t minMeasurement, uint16_t maxMeasurement, uint16_t maxSteps){
  uint16_t steps;
  if (noiseMeasurement > maxMeasurement){
    steps = maxSteps;
  }else if (noiseMeasurement < minMeasurement){
    steps = 0;
  }else{
    steps = maxSteps * (noiseMeasurement - minMeasurement) / (maxMeasurement - minMeasurement);
  }
  return steps;
}

void Utils::deviceName(String &mac_address, String &deviceId){
#if defined(ESP8266)
#define HOSTNAME_PREFIX "esp8266_"
#endif
#if defined(ESP32)
#define HOSTNAME_PREFIX "esp32_"
#endif
  deviceId.clear();
  deviceId.concat(HOSTNAME_PREFIX);
  deviceId.concat(mac_address.substring(9,11));
  deviceId.concat(mac_address.substring(12,14));
  deviceId.concat(mac_address.substring(15));
  deviceId.toLowerCase();
}

void Utils::deviceHostname(String &device_name, String &device_mdns){
  device_mdns.clear();
  device_mdns.concat(device_name);
  device_mdns.concat(".local");
}