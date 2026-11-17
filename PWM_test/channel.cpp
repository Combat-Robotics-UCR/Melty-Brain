#include "channel.h"

void IRAM_ATTR channel::ISR() {
  unsigned long now = micros();  //
  if (digitalRead(_PIN) == HIGH) { //
    _riseTime = now; // 
  } else { //
    _widthUs = now - _riseTime; //
    _update = true; //
  }
}

void channel::init(uint8_t pin) {
  _PIN = pin;
  pinMode(_PIN, INPUT);
  attachInterruptArg(digitalPinToInterrupt(_PIN), wrapper, this, CHANGE);
}

bool channel::updated(){
  return _update;
}

float channel::getdata() {
  _update = false;
  return ((_widthUs - 1522) / 5.23f);
}