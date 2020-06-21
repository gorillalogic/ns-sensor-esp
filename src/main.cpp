/**
 * Noise Sensor
 *
 * 1. Reads noise sensor and sends it to Serial to be plotted at 9600 baud.
 * 2. Creates a pattern to NeoPixel Ring according to the magnitude of the noise signal.
 * 3. Sends data via MQTT every second.
 */

#include <FS.h>
#include <Arduino.h>
#include <ArduinoLog.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266_Utils_OTA.h>
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
#include "analog_multiplexor.h"

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
  config::mqtt::channels::NOISE,
  WiFi.macAddress()
);

AnalogSensor noise_primary(
  config::sampling::noise_primary::NAME,
  config::pins::ANALOG_READ,
  &mqtt,
  config::pins::noise_primary::CONTROL_PIN
);

AnalogMultiplexor multiplexor;

void setup() {
  Serial.begin(config::serial::BAUD_RATE);
  Log.begin(LOG_LEVEL, &Serial, true);
  ledRing.setup();
  wifi.connect();
  mDNS.assign();
  initOTA();
  ArduinoOTA.setHostname(config::mdns::HOSTNAME.domain);
  mqtt.connect();
  multiplexor.addAnalogSensor(&noise_primary);
}

void loop() {
  ArduinoOTA.handle();
  mDNS.update();

  AnalogSensor* sensor = multiplexor.rotate();
  uint16_t noiseValue = sensor->nextCycle();

  int leds = Utils::calculateLeds(
    noiseValue,
    config::sampling::noise_primary::raw::THRESHOLD_MIN,
    config::sampling::noise_primary::raw::THRESHOLD_MAX,
    config::leds::LEDS_TOTAL
  );
  animations.noiseMagnitude(leds);
  Log.verbose(logger::leds::displayLedsCount, noiseValue, leds);

  delay(config::sampling::DELAY_MS);
}
