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

    static void IRAM_ATTR wrapper(void* bridge) { static_cast<channel*>(bridge)->ISR(); }
    void IRAM_ATTR ISR();

  public:
    void init(uint8_t);
    bool updated();
    float getdata();
};

#endif  // CHANNEL_H
