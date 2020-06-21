#include "types.h"

namespace config {
  namespace wifi {
    const Credentials HOME = { "IoT", "42noisealert42" };
    const Credentials WORK = { "GorillaGuest", "gorillalogicguest" };
    const Credentials PHONE = { "iPhone-Emma", "@noise42@" };

    const vector<Credentials> NETWORKS = { HOME, WORK, PHONE };
  }

  namespace mdns {
    const Hostname LOCAL = { "noise-sensor-8b6ad8", "noise-sensor-8b6ad8.local" };
    const Hostname COLLECTOR = { "noise-collector-8b6ad8", "noise-collector-8b6ad8.local" };
    const Hostname &SENSOR = LOCAL;
  }

  namespace mqtt {
    const int RETRIES = 3;
    const char* USERNAME = "noise";
    const Credentials DEFAULT_CREDENTIALS = { "noise", "42noisealert42" };
    const Config DEFAULT_CONFIG = { 1883, mdns::COLLECTOR };

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
      const int SIGNAL_READ = A0;
    }
    namespace leds {
      const int VIN = 14;
    }
  }

  namespace leds {
    const int LEDS_TOTAL = 24;

    namespace animations {
      const double LOW = 0.75;
      const double HIGH = 1;
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
