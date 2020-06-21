#include <Adafruit_NeoPixel.h>

class LedRing{
  private:
    Adafruit_NeoPixel strip;
    const uint32_t green;
    const uint32_t blue;
    const uint32_t yellow;
    const int totalLeds;
    const int pinVIN;

  public:
    explicit Leds(int totalLeds, int pinVIN);
    ~Leds();

    void setup();
    void clear();
    int getTotalLeds();
    int getPinVIN();
    Adafruit_NeoPixel &getStrip();
}