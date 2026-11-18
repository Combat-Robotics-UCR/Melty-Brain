#ifndef MOTOR_H
#define MOTOR_H

//#define WIDTH_LOW_US      968
#define WIDTH_MIDDLE_US       1515
#define WIDTH_HIGH_US         2046
#define PWM_FREQUENCY_HZ      59
#define PWM_RESOLUTION_BITS   16

#include <Arduino.h>

class motor {
  private:
    uint8_t _pin = 0;
    const float _middle_duty = WIDTH_MIDDLE_US * PWM_FREQUENCY_HZ * (65536.0 / 1000000.0);
    const float _high_duty = WIDTH_HIGH_US * PWM_FREQUENCY_HZ * (65536.0 / 1000000.0);

  public:
    void init(uint8_t);
    void set_speed(const float&); // anything from 0 -> 100
};

#endif  // MOTOR_H
