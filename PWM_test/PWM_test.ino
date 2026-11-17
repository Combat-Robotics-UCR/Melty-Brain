#include "motor.h"
#include "channel.h"

const int PWM_PIN = 13;
const int MOTOR_PIN = 21;

motor m1;
channel c1;

void setup() {
  Serial.begin(115200);
  m1.init(MOTOR_PIN);
  c1.init(PWM_PIN);
}

// example usage
// if (c1.updated()) {
//   m1.set_speed(c1.getdata());
// }

void loop() {
  if (c1.updated()) {
    m1.set_speed(c1.getdata());
  }
}