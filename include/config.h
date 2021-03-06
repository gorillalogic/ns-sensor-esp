#pragma once

#include <Arduino.h>
#include <vector>
#include "types.h"

/* DEBUG Levels
 * 0 - LOG_LEVEL_SILENT     no output
 * 1 - LOG_LEVEL_FATAL      fatal errors
 * 2 - LOG_LEVEL_ERROR      all errors
 * 3 - LOG_LEVEL_WARNING    errors, and warnings
 * 4 - LOG_LEVEL_NOTICE     errors, warnings and notices
 * 5 - LOG_LEVEL_TRACE      errors, warnings, notices & traces
 * 6 - LOG_LEVEL_VERBOSE    all
*/
#define LOG_LEVEL LOG_LEVEL_NOTICE

/* Constants */
namespace config {
  namespace wifi {
    const WifiCredentials HOME = { "IoT", "42noisealert42" };
    const WifiCredentials WORK = { "GorillaGuest", "gorillalogicguest" };
    const WifiCredentials PHONE = { "iPhone-Emma", "@noise42@" };

    const std::vector<WifiCredentials> NETWORKS = { HOME, WORK, PHONE };
  }

  namespace mdns {
    const Hostname COLLECTOR = { "noise-collector-8b6ad8", "noise-collector-8b6ad8.local" };
  }

  namespace mqtt {
    const uint8_t RETRIES = 3;
    const char * const USERNAME = "noise";
    const MqttCredentials DEFAULT_CREDENTIALS = { "noise", "42noisealert42" };
    const MqttConfig DEFAULT_CONFIG = { mdns::COLLECTOR, 1883 };

    namespace channels {
      const char * const NOISE = "sensors/noise";
    }
  }

  namespace serial {
    const uint32_t BAUD_RATE = 9600;
    const uint8_t BRIGHTNESS = 5;
  }

/**
 * There is only one ADC so we need to use DIGITAL READ for the others sensors,
 * this requires a separate ADC for each of them or a different board or sensors
 * with an integrated ADC.
 * For testing purposes we can mock a signal in those pins by using another board
 * like an ATMega2560 which I own to simulate other sensors output.
*/
  namespace pins {

    const uint8_t NO_CONTROL = 0xFF;
#if defined(ESP8266)
    const uint8_t ANALOG_READ = A0;

    namespace noise_primary {
      const uint8_t CONTROL_PIN = 12;
    }

    namespace noise_secondary {
      const uint8_t CONTROL_PIN = 13;
    }

    namespace leds {
      const uint8_t VIN = 14;
    }
  }
#endif
#if defined(ESP32)
    const uint8_t ANALOG_READ = 36;

    namespace noise_primary {
      const uint8_t CONTROL_PIN = 12;
    }

    namespace noise_secondary {
      const uint8_t CONTROL_PIN = 13;
    }

    namespace leds {
      const uint8_t VIN = 14;
    }
  }
#endif

  namespace leds {
    const uint16_t LEDS_TOTAL = 24;

    namespace animations {
      const double THRESHOLD_LOW = 0.25;
      const double THRESHOLD_HIGH = 0.75;
    }
  }

  namespace sampling {
    const uint16_t NORMAL_RATE = 5;
    const uint16_t SLOW_RATE = 500;

    const uint16_t DELAY_MS = NORMAL_RATE;
    const uint16_t AVERAGE_COUNT = 100;

    namespace noise_primary {
      const char * const NAME = "noise_primary";
      namespace raw {
        const uint16_t THRESHOLD_MAX = 1000;
        const uint16_t THRESHOLD_MIN = 0;
      }
    }

    namespace noise_secondary {
      const char * const NAME = "noise_secondary";
      namespace raw {
        const uint16_t THRESHOLD_MAX = 1000;
        const uint16_t THRESHOLD_MIN = 0;
      }
    }

    namespace temperature {
      const char * const NAME = "temperature";
    }

    namespace humidity {
      const char * const NAME = "humidity";
    }

    namespace proximity {
      const char * const NAME = "proximity";
    }
  }
}
