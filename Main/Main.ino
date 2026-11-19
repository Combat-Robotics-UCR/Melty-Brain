#include "Config.h"
#include "Led.h"
#include "Heading.h"
#include "Imu.h"
#include "motor.h"
#include "channel.h"

motor m1, m2;
channel rc1, rc2, rc3;

float angle_diff(float a, float b) {
  float d = fmod(a - b, TWO_PI);
  if (d > PI) d -= TWO_PI;
  if (d < -PI) d += TWO_PI;
  return d;
}

void setup() {
  Serial.begin(115200);

  led_init();

  if (!imu_init()) {
    Serial.println("MPU6050 not found - check wiring");
    while (true) {
      led_blink_code(2);
    }
  }

  imu_calibrate();

  heading_init();

  led_blink_code(3);

  delay(1000);
  rc1.init(RC1);
  rc2.init(RC2);
  rc3.init(RC3);

  m2.init(MOTOR1);
  m1.init(MOTOR2);

  delay(1000);

  m2.set_speed(0);
  m1.set_speed(0);
  delay(10000);
  Serial.println("hi");
}

void loop() {
  static bool enabled = false;
  if (rc3.updated()) {
    float command3 = rc3.getdata();
    // Serial.print("three:");
    // Serial.println(command3);
    if (command3 > 15) {
      enabled = true;
    } else {
      enabled = false;
      m2.set_speed(0);
      m1.set_speed(0);
    }
  }

  static uint8_t count1 = 0;
  if (rc1.updated()) {
    float command1 = rc1.getdata();
    if (command1 < 10 && command1 > -15) {
      count1++;
      if (count1 > 20 && enabled) {
        // Serial.print("one:");
        // Serial.println(command1);
        m1.set_speed(command1);
        // Serial.println(1);
        count1 = 0;
      }
    }
  }

  static uint8_t count2 = 0;
  if (rc2.updated()) {
    float command2 = rc2.getdata();
    if (command2 < 10 && command2 > 0) {
      count2++;
      if (count2 > 20 && enabled) {
        // Serial.print("two:");
        // Serial.println(command2);
        m2.set_speed(command2);
        // Serial.println(2);
        count2 = 0;
      }
    }
  }

  imu_read();
  heading_update(imu_get_omega());
  float heading = heading_get();
  led_update(heading);
}
