#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Imu.h"
#include "Config.h"

static Adafruit_MPU6050 mpu;
static float gyro_z = 0;
static float ax = 0, ay = 0;
static float gyro_bias = 0;

bool imu_init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  if (!mpu.begin()) {
    return false;
  }
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);

  return true;
}

void imu_calibrate() {
  float total = 0;
  for (int i = 0; i < 500; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    total = total + g.gyro.z;
    delay(2);
  }
  gyro_bias = total / 500;
}

void imu_read() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  gyro_z = g.gyro.z - gyro_bias;
  ax = a.acceleration.x;
  ay = a.acceleration.y;
}

float imu_get_omega() {
  if (abs(gyro_z) < GYRO_LIMIT) {
    return gyro_z;
  }
  float accel = sqrt(ax * ax + ay * ay);
  float omega = sqrt(accel / IMU_RADIUS);
  if (gyro_z < 0) omega = -omega;
  return omega;
}
