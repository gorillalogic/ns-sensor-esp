/**
 * Noise Sensor
 *
 * 1. Reads noise sensor and sends it to Serial to be plotted at 9600 baud.
 * 2. Creates a pattern to NeoPixel Ring according to the magnitude of the noise signal.
 * 3. Sends data via MQTT every second.
 */
#include "types.h"
#include "config.h"
#include "logger.h"
#include "wifi.h"
#include "mdns.h"
#include "mqtt.h"
#include "sampling.h"
#include "led_ring.h"
#include "animations.h"
#include "transforms.h"
#include <vector>

LedRing ledRing(
  config::sampling::noise::rate::AVERAGE_COUNT,
  config::pins::leds::VIN
);

Animations animations(
  ledRing,
  config::leds::animations::THRESHOLD_LOW,
  config::leds::animations::THRESHOLD_HIGH
);

Transforms transforms = Transforms();

Sampling sampling(
  config::sampling::noise::rate::AVERAGE_COUNT,
  config::mdns::HOSTNAME.name
);

Wifi wifi = Wifi();

Mdns mDNS = Mdns();


Mqtt mqtt(
  config::mqtt::DEFAULT_CONFIG,
  config::mqtt::DEFAULT_CREDENTIALS,
  config::mqtt::channels::NOISE
);

void setup() {
  Serial.begin( config::serial::BAUD_RATE );
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  ledRing.setup();
  wifi.connect();
  mDNS.assign();
  mqtt.connect();
}

void loop() {
  mDNS.update();

  int noiseValue = analogRead( config::pins::noise::SIGNAL_READ );

  int steps = transforms.discreteSteps(
    noiseValue,
    config::sampling::noise::raw::THRESHOLD_MAX,
    config::sampling::noise::raw::THRESHOLD_MIN,
    config::leds::LEDS_TOTAL
  );

  sampling.add( noiseValue );

  animations.noiseMagnitude( steps );

  if ( sampling.enoughSamples() ){
    SensorPayload payload = sampling.read();
    mqtt.publish(payload);
    sampling.clear();
  }

  delay( config::sampling::DELAY_MS );
}
