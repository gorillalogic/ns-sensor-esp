#pragma once

#include <IPAddress.h>

class NS_mDNS{
  public:
    explicit NS_mDNS();
    ~NS_mDNS();

    void queryCollectorHost(IPAddress &result);
    void assign();
    void update();
    bool clear();

  private:
    const char *query;
    IPAddress result;
};
