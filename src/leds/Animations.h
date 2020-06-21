#include <Adafruit_NeoPixel.h>

class Animations {
  private:
    LedRing &ledRing;
    int high;
    int low;

  public:
    explicit Animations(LedRing &ledRing, double ratioLow, double ratioHigh);
    ~Animations();

    void clear();
    void noiseMagnitude(int steps);
};