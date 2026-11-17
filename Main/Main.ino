#include "Config.h"
#include "Led.h"
#include "Heading.h"
#include "Imu.h"
#include "Motor.h"
#include "Radio.h"

float angle_diff(float a, float b) {
  float d = fmod(a - b, TWO_PI);
  if (d > PI) d -= TWO_PI;
  if (d < -PI) d += TWO_PI;
  return d;
}

void setup() {
  Serial.begin(115200);
  led_init();
  //motor_init();
  //radio_init();
  if (!imu_init()) {
    Serial.println("MPU6050 not found - check wiring");
    digitalWrite(ERROR_LED, HIGH);
    while (true) {
      led_blink_code(2);
    }
  }

  imu_calibrate();

  led_blink_code(3);

  heading_init();
}

void loop() {
  //radio_update();
  imu_read();
  heading_update(imu_get_omega());
  float heading = heading_get();
  led_update(heading);

  /*if (!radio_connected()) {
    motor_stop();
    return;
  }
  */

  /*float throttle = radio_throttle();  // 0.0 to 1.0
  float x = radio_steer_x();          // -1.0 to 1.0
  float y = radio_steer_y();          // -1.0 to 1.0
*/

  /*if (throttle < THROTTLE_DEADZONE) {
    motor_stop();
    return;
    */
}
// Spin in place: both wheels get the throttle
/*float left = throttle;
float right = throttle; */

// Move: give the RIGHT wheel extra power while it faces the stick direction
/* float power = sqrt(x * x + y * y);
  if (power > STICK_DEADZONE) {
    if (power > 1.0) power = 1.0;
    float target = atan2(-x, y);
    float facing = cos(angle_diff(heading + FORWARD, target));
    if (facing > 0) {
      right = right + DRIVE_BOOST * power * facing;
    }
  }
  */

//motor_set(left, right);
//}
