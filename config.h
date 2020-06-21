#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <vector>

#include "types.h"

namespace config {
  namespace wifi {
    const WifiCredentials HOME = { "IoT", "42noisealert42" };
    const WifiCredentials WORK = { "GorillaGuest", "gorillalogicguest" };
    const WifiCredentials PHONE = { "iPhone-Emma", "@noise42@" };

    const std::vector<WifiCredentials> NETWORKS = { HOME, WORK, PHONE };
  }

  namespace mdns {
    const Hostname HOSTNAME = { "noise-sensor-8b6ad8", "noise-sensor-8b6ad8.local" };
    const Hostname COLLECTOR = { "noise-collector-8b6ad8", "noise-collector-8b6ad8.local" };
    const Hostname &SENSOR = HOSTNAME;
  }

  namespace mqtt {
    const int RETRIES = 3;
    const char* USERNAME = "noise";
    const MqttCredentials DEFAULT_CREDENTIALS = { "noise", "42noisealert42" };
    const MqttConfig DEFAULT_CONFIG = { mdns::COLLECTOR, 1883 };

    namespace channels {
      const char *NOISE = "sensors/noise";
    }
  }

  namespace serial {
    const int BAUD_RATE = 9600;
    const int BRIGHTNESS = 5;
  }

  namespace pins {
    namespace noise {
      const int SIGNAL_READ = 0; //A0;
    }
    namespace leds {
      const int VIN = 14;
    }
  }

  namespace leds {
    const int LEDS_TOTAL = 24;

    namespace animations {
      const double THRESHOLD_LOW = 0.75;
      const double THRESHOLD_HIGH = 1;
    }
  }

  namespace sampling {
    const int DELAY_MS = 5;

    namespace noise {
      namespace raw {
        const int THRESHOLD_MAX = 700;
        const int THRESHOLD_MIN = 400;
      }
      namespace rate {
        const int AVERAGE_COUNT = 100;
      }
    }
  }
}

#endif /* _CONFIG_H_ */
