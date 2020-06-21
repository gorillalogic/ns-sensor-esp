#pragma once

namespace logger {
  namespace wifi {
    const char * const connecting = "Wifi: Connecting ...";
    const char * const connected = "Wifi: Connected.";
  }

  namespace mdns {
    const char * const started = "mDNS: started.";
    const char * const responderStarted = "mDNS responder started";
    const char * const setupError = "mDNS: Error setting up MDNS responder!";
  }

  namespace mqtt {
    const char * const connecting = "MQTT: Connecting...";
    const char * const retrying = "MQTT: Retrying connection in 5 seconds...";
    const char * const connected = "MQTT: Connected!";
    const char * const failedSending = "MQTT: Failed sending.";
  }
}
