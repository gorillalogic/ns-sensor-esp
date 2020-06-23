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
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <EasyOTA.h>
#include <vector>
#include "types.h"
#include "config.h"
#include "logger.h"
#include "ns_wifi.h"
#include "ns_mdns.h"
#include "ns_mqtt.h"
#include "sampling.h"
#include "led_ring.h"
#include "animations.h"
#include "utils.h"
#include "analog_sensor.h"
#include "digital_sensor.h"
#include "analog_multiplexor.h"

WiFiClient wifiClient;
PubSubClient pubSubClient(wifiClient);

IPAddress server_ip;
String mac_address;

LedRing ledRing(
  config::leds::LEDS_TOTAL,
  config::pins::leds::VIN
);

Animations animations(
  ledRing,
  config::leds::animations::THRESHOLD_LOW,
  config::leds::animations::THRESHOLD_HIGH
);

NS_WiFi wifi = NS_WiFi(
  config::wifi::NETWORKS
);

NS_mDNS mDNS = NS_mDNS();

NS_MQTT mqtt = NS_MQTT(
    wifiClient,
    pubSubClient
);

AnalogSensor noise_primary(
  config::sampling::noise_primary::NAME,
  config::pins::ANALOG_READ,
  &mqtt,
  config::pins::noise_primary::CONTROL_PIN
);

AnalogSensor noise_secondary(
  config::sampling::noise_secondary::NAME,
  config::pins::ANALOG_READ,
  &mqtt,
  config::pins::noise_secondary::CONTROL_PIN
);

AnalogMultiplexor multiplexor;

void setup() {
  /* Logs */
  Serial.begin(config::serial::BAUD_RATE);
  Log.begin(LOG_LEVEL, &Serial, true);

  /* WiFi */
  wifi.connect();
  mac_address = WiFi.macAddress();
  mqtt.setMacAddress(mac_address);
  Log.notice("MAC Address: %s" CR, mac_address.c_str());

  /* mDNS */
  mDNS.assign();
  do{
    mDNS.queryCollectorHost(server_ip);
  }while( server_ip[0] != 192 );
  mqtt.setServerIP(server_ip);
  Log.notice("Found Collector IP at %s" CR, server_ip.toString().c_str());

  /* OTA */
  initOTA();
  ArduinoOTA.setHostname(config::mdns::HOSTNAME.domain);

  /* Sensors */
  multiplexor.addAnalogSensor(&noise_primary);
  multiplexor.addAnalogSensor(&noise_secondary);

  /* Leds */
  ledRing.setup();
  Log.notice("LED RING: started." CR);
}

void loop() {
  ArduinoOTA.handle();
  mDNS.update();
  mqtt.connect();
  mqtt.loop();

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
