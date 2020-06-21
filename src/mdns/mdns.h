#ifndef _MDNS_H_
#define _MDNS_H_

class Mdns{
  public:
    explicit Mdns();
    ~Mdns();

    void assign();
    void update();
    void start();
    bool clear();
};

#endif /* _MDNS_H_ */
