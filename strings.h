#ifndef LOGGER_H
#define LOGGER_H

namespace logger {
  namespace wifi {
    const char *connecting = "Wifi: Connecting ...";
    const char *connected = "Wifi: Connected.";
  }

  namespace mdns {
    const char *started = "mDNS: started.";
    const char *responderStarted = "mDNS responder started";
    const char *setupError = "mDNS: Error setting up MDNS responder!";
  }

  namespace mqtt {
    const char *connecting = "MQTT: Connecting...";
    const char *retrying = "MQTT: Retrying connection in 5 seconds...";
    const char *connected = "MQTT: Connected!";
    const char *failedSending = "MQTT: Failed sending.";
  }
}

#endif /* LOGGER_H */