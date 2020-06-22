#pragma once

class NS_mDNS{
  public:
    explicit NS_mDNS();
    ~NS_mDNS();

    const char *queryCollectorHost();
    void assign();
    void update();
    bool clear();
};
