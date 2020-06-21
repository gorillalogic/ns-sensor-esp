#include "config.h"

using namespace std;

class Wifi {
  private:
    ESP8266WiFiMulti wifiMulti;
    string ipAddress;

  public:
    explicit Wifi();
    ~Wifi();

    bool isConnected();
    string currentIpAddress();
    void connect();
    void disconnect();
}
