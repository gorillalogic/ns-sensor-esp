/**
 * Noise Sensor
 *
 * 1. Reads noise sensor and sends it to Serial to be plotted at 9600 baud.
 * 2. Creates a pattern to NeoPixel Ring according to the magnitude of the noise signal.
 * 3. Sends data via MQTT every second.
 */

#include <Arduino.h>
#include <ArduinoLog.h>
#include <vector>
#include "types.h"
#include "config.h"
#include "logger.h"
#include "wifi.h"
#include "mdns.h"
#include "mqtt.h"
#include "sampling.h"
#include "led_ring.h"
#include "animations.h"
#include "utils.h"
#include "analog_sensor.h"
#include "digital_sensor.h"

LedRing ledRing(
  config::leds::LEDS_TOTAL,
  config::pins::leds::VIN
);

Animations animations(
  ledRing,
  config::leds::animations::THRESHOLD_LOW,
  config::leds::animations::THRESHOLD_HIGH
);

Wifi wifi = Wifi(
  config::wifi::NETWORKS
);

Mdns mDNS = Mdns();

Mqtt mqtt(
  config::mqtt::DEFAULT_CONFIG,
  config::mqtt::DEFAULT_CREDENTIALS,
  config::mqtt::channels::NOISE
);

AnalogSensor noise(
  config::sampling::noise::NAME,
  config::pins::noise::ANALOG_READ,
  &mqtt
);

DigitalSensor temperature(
  config::sampling::temperature::NAME,
  config::pins::temperature::DIGITAL_READ,
  &mqtt
);

DigitalSensor humidity(
  config::sampling::humidity::NAME,
  config::pins::humidity::DIGITAL_READ,
  &mqtt
);

DigitalSensor proximity(
  config::sampling::proximity::NAME,
  config::pins::proximity::DIGITAL_READ,
  &mqtt
);

void setup() {
  Serial.begin(115200);
  Serial.begin(config::serial::BAUD_RATE);
  Log.begin(LOG_LEVEL, &Serial, true);
  ledRing.setup();
  wifi.connect();
  mDNS.assign();
  mqtt.connect();
}

void loop() {
  mDNS.update();

  uint16_t noiseValue = noise.nextCycle();
  temperature.nextCycle();
  humidity.nextCycle();
  proximity.nextCycle();

  int leds = Utils::calculateLeds(
    noiseValue,
    config::sampling::noise::raw::THRESHOLD_MIN,
    config::sampling::noise::raw::THRESHOLD_MAX,
    config::leds::LEDS_TOTAL
  );
  animations.noiseMagnitude(leds);
  Log.verbose(logger::leds::displayLedsCount, noiseValue, leds);

  delay(config::sampling::DELAY_MS);
}
