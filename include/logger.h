#pragma once

#include <ArduinoLog.h>

namespace logger {
  namespace wifi {
    // notice
    const char * const connecting = "Wifi: Connecting ..." CR;
    const char * const connected = "Wifi: Connected." CR;
    const char * const addingCredentials = "Adding credentials %s %s" CR;

    //verbose
    const char * const ssid = "SSID: %s" CR;
    const char * const ip = "IP address: %s" CR;
  }

  namespace mdns {
    //notice
    const char * const started = "mDNS: started." CR;
    const char * const responderStarted = "mDNS responder started" CR;

    //error
    const char * const setupError = "mDNS: Error setting up MDNS responder!" CR;
  }

  namespace mqtt {
    //notice
    const char * const connecting = "MQTT: Connecting..." CR;
    const char * const retrying = "MQTT: Retrying connection in 5 seconds..." CR;
    const char * const connected = "MQTT: Connected!" CR;

    //error
    const char * const failedSending = "MQTT: Failed sending." CR;
    const char * const failedSendingLimitTries = "Mqtt: Failed %d times. Restarting connection" CR;

    //verbose
    const char * const payloadSent = "Mqtt: Sent %s %d %d %d" CR;
  }

  namespace sampling {
    //verbose
    const char * const addSampling = "Sampling: Adding value: %d, min: %d, max: %d, sum: %d" CR;
    const char * const readSampling = "Sampling: Read deviceId: %s, min: %d, max: %d, avg: %d / %d = %d" CR;
  }

  namespace leds {
    //verbose
    const char * const displayLedsCount = "Led Animation: Magnitude value: %d,\tcount: %d" CR;
  }
}
