#pragma once

class NS_mDNS{
  public:
    explicit NS_mDNS();
    ~NS_mDNS();

    void assign();
    void update();
    void start();
    bool clear();
};
