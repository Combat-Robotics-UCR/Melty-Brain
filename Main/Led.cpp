#include <Arduino.h>
#include "Led.h"
#include "Config.h"

void led_init() {

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
}

void led_update(float heading) {
  heading = heading + FORWARD;
  heading = fmod(heading, TWO_PI);
  if (heading < 0) heading += TWO_PI;
  if (heading < BLINK_WIDTH / 2 || heading > TWO_PI - BLINK_WIDTH / 2) {  // line D
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void led_blink_code(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
  delay(1000);
}
