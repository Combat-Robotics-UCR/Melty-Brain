#include "Config.h"
#include "Led.h"
#include "Heading.h"
#include "Imu.h"
#include "motor.h"
#include "channel.h"

// motor test code -------------------------
#include <Preferences.h>
Preferences preferences;
// -----------------------------------------

motor m1, m2;
channel rc1, rc2;

float angle_diff(float a, float b) {
  float d = fmod(a - b, TWO_PI);
  if (d > PI) d -= TWO_PI;
  if (d < -PI) d += TWO_PI;
  return d;
}

void setup() {
  Serial.begin(115200);
  preferences.begin("radius", false);
  Serial.println(preferences.getFloat("r", 0.0));

  led_init();

  //rc1.init(RC2);
  // rc2.init(RC2);
  // rc3.init(RC3);
  // rc4.init(RC4);

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

  m2.init(MOTOR1);
  m1.init(MOTOR2);

  delay(1000);

  m2.set_speed(0);
  m1.set_speed(0);
  delay(10000);
  Serial.println("hi");
}

void loop() {
  if (rc1.updated()) {
    float command1 = rc1.getdata();
    //Serial.println(command1);
    if (command1 < 10 && command1 > 0) {
      m1.set_speed(command1);
      m2.set_speed(command1);
    }
  }

  if (rc1.updated()) {
    float command2 = rc2.getdata();
    Serial.println(command2);
    if (command2 > 50.0) {
      imu_set_radius(0.001); // incrememnt by 1mm
      preferences.putFloat("r", IMU_RADIUS);
    } else if (command2 < -50.0) {
      imu_set_radius(-0.001); // decrement by 1mm
      preferences.putFloat("r", IMU_RADIUS);
    }
  }

  imu_read();
  heading_update(imu_get_omega());
  float heading = heading_get();
  led_update(heading);
}
