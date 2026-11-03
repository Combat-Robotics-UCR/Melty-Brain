#include <Arduino.h>
#include "Heading.h"

static float heading = 0;
static unsigned long last_time = 0;

void heading_init() {
  heading = 0;
  last_time = micros();
}

void heading_update(float omega) {
  unsigned long now = micros();
  float dt = (now - last_time) / 1000000.0;
  last_time = now;
  heading = heading + omega * dt;
  heading = fmod(heading, TWO_PI);
  if (heading < 0) heading += TWO_PI;
}

float heading_get() {
  return heading;
}

//explode!!!! - My Gf's code dont delete - Lucas

