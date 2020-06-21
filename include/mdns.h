#pragma once

class Mdns{
  public:
    explicit Mdns();
    ~Mdns();

    void assign();
    void update();
    void start();
    bool clear();
};
