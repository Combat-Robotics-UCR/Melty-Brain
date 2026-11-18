#include "motor.h"

void motor::init(uint8_t pin){
  _pin = pin;
  ledcAttach(_pin, PWM_FREQUENCY_HZ, PWM_RESOLUTION_BITS);
}

// anything from 0 -> 100
// duty = pulse_us * freq * total resolution / 1,000,000
// 1523 -> 2046 maps to 5490 -> 7375
// so step size of 18.85
void motor::set_speed(const float& speed){
  ledcWrite(_pin, (speed * ((_high_duty - _middle_duty) / 100.0)) + _middle_duty);
  // Serial.println(_pin);
  // Serial.println((speed * ((_high_duty - _middle_duty) / 100.0)) + _middle_duty);
}