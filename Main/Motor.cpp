#include <Arduino.h>
#include <ESP32Servo.h>
#include "Motor.h"
#include "Config.h"

static Servo esc1;
static Servo esc2;

void motor_init() {
  esc1.setPeriodHertz(50);
  esc2.setPeriodHertz(50);

  esc1.attach(MOTOR1, ESC_MIN, ESC_MAX);
  esc2.attach(MOTOR2, ESC_MIN, ESC_MAX);

  motor_stop();
  delay(ESC_ARM);
}

void motor_set(float m1, float m2) {
  m1 = constrain(m1, 0.0, 1.0);
  m2 = constrain(m2, 0.0, 1.0);

  int us1 = ESC_MIN + m1 * (ESC_MAX - ESC_MIN);
  int us2 = ESC_MIN + m2 * (ESC_MAX - ESC_MIN);

  esc1.writeMicroseconds(us1);
  esc2.writeMicroseconds(us2);
}

void motor_stop() {

  esc1.writeMicroseconds(ESC_MIN);
  esc2.writeMicroseconds(ESC_MIN);
}
