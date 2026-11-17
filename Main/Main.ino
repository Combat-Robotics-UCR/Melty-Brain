#include "Config.h"
#include "Led.h"
#include "Heading.h"
#include "Imu.h"
#include "motor.h"
#include "channel.h"

motor m1, m2;
channel rc1, rc2, rc3, rc4;

float angle_diff(float a, float b) {
  float d = fmod(a - b, TWO_PI);
  if (d > PI) d -= TWO_PI;
  if (d < -PI) d += TWO_PI;
  return d;
}

void setup() {
  Serial.begin(115200);

  led_init();

  m1.init(MOTOR1);
  m2.init(MOTOR2);

  rc1.init(RC1);
  // rc2.init(RC2);
  // rc3.init(RC3);
  // rc4.init(RC4);

  if (!imu_init()) {
    Serial.println("MPU6050 not found - check wiring");
    digitalWrite(ERROR_LED, HIGH);
    while (true) {
      led_blink_code(2);
    }
  }

  imu_calibrate();

  heading_init();

  led_blink_code(3);
}

void loop() {
  if (rc1.updated()) {
    m1.set_speed(rc1.getdata());
    m2.set_speed(rc1.getdata());
  }

  imu_read();
  heading_update(imu_get_omega());
  float heading = heading_get();
  led_update(heading);
}
