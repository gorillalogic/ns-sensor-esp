#pragma once

#include <ArduinoLog.h>

namespace logger {
  namespace wifi {
    const char * const connecting = "Wifi: Connecting ..." CR;
    const char * const connected = "Wifi: Connected." CR;
  }

  namespace mdns {
    const char * const started = "mDNS: started." CR;
    const char * const responderStarted = "mDNS responder started" CR;
    const char * const setupError = "mDNS: Error setting up MDNS responder!" CR;
  }

  namespace mqtt {
    const char * const connecting = "MQTT: Connecting..." CR;
    const char * const retrying = "MQTT: Retrying connection in 5 seconds..." CR;
    const char * const connected = "MQTT: Connected!" CR;
    const char * const failedSending = "MQTT: Failed sending." CR;
  }
}
