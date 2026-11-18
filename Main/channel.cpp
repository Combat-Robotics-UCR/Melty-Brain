#include "channel.h"

void IRAM_ATTR channel::ISR(void* object) {
  unsigned long now = micros();
  channel* c = static_cast<channel*>(object);

  if (gpio_get_level((gpio_num_t)c->_PIN)) {
    c->_riseTime = now;
    c->_haveRise = true;
  } else if (c->_haveRise) {
    c->_widthUs = now - c->_riseTime;
    c->_haveRise = false;
    c->_update = true;
  }
}

void channel::init(uint8_t pin) {
  _PIN = pin;
  pinMode(_PIN, INPUT);
  attachInterruptArg(digitalPinToInterrupt(_PIN), ISR, this, CHANGE);
}

float channel::getdata() {
  noInterrupts();
  unsigned long w = _widthUs;
  _update = false;
  interrupts();

  return (w - 1515.0) / 5.35;
}