#pragma once

#include "types.h"

class Utils{
  public:
    static uint16_t calculateLeds(uint16_t noiseMeasurement, uint16_t minMeasurement, uint16_t maxMeasurement,
      uint16_t steps);
    static void deviceName(String &mac_address, String &device_id);
    static void deviceHostname(String &device_name, String &device_mdns);
};
