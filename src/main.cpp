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

LedRing ledRing(
  config::leds::LEDS_TOTAL,
  config::pins::leds::VIN
);

Animations animations(
  ledRing,
  config::leds::animations::THRESHOLD_LOW,
  config::leds::animations::THRESHOLD_HIGH
);

Sampling sampling(
  config::sampling::noise::rate::AVERAGE_COUNT,
  config::mdns::HOSTNAME.name
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

  int noiseValue = analogRead(config::pins::noise::SIGNAL_READ);
  sampling.add( noiseValue );
  if ( sampling.enoughSamples() ){
    SensorPayload payload = sampling.read();
    mqtt.publish(payload);
    sampling.clear();
  }

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
