/**
 * Noise Sensor
 *
 * 1. Reads noise sensor and sends it to Serial to be plotted at 9600 baud.
 * 2. Creates a pattern to NeoPixel Ring according to the magnitude of the noise signal.
 * 3. Sends data via MQTT every second.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif


#include "config.h"
#include "log.h"
#include "src/wifi/wifi.h"
#include "src/mdns/mdns.h"
#include "src/mqtt/mqtt.h"
#include "src/sampling/sampling.h"
#include "src/leds/animations.h"
#include "src/utils/transforms.h"

using namespace std;

Animations animations();
Transforms transforms();
Sampling sampling(
  config::sampling::noise::rate::AVERAGE_COUNT,
  config::mdns::LOCAL
);
Wifi wifi();
Mqtt mqtt(
  config::mdns::LOCAL,
  config::mdns::COLLECTOR,
  config::mqtt::DEFAULT_CREDENTIALS,
  config::mqtt::DEFAULT_CONFIG,
  config::mqtt::channels::NOISE
);
MDns mDNS();


void setup() {
  Serial.begin( config::serial::BAUD_RATE );

  animations.setup();
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
    config::leds::animations::LEDS_TOTAL
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
