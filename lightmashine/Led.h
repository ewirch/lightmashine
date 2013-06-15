#ifndef __LED_H__
#define __LED_H__

class Led {
  public:
    virtual void set(byte percent) = 0;
    virtual void update() = 0;
};

#endif
