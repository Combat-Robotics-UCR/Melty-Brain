#ifndef CHANNEL_H
#define CHANNEL_H

#include "esp32-hal-gpio.h"
#include <stdint.h>
#include <Arduino.h>

class channel {
  private:
    uint8_t _PIN = 0;

    volatile unsigned long _widthUs = 0;
    volatile unsigned long _riseTime = 0;
    volatile bool _update = false;
    volatile bool _haveRise = false;

    //static void IRAM_ATTR wrapper(void* object) { static_cast<channel*>(object)->ISR(); }
    static void IRAM_ATTR ISR(void* object);

  public:
    void init(uint8_t);
    bool updated() { return _update; }
    float getdata();
};

#endif  // CHANNEL_H
