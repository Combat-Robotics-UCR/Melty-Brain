#pragma once

bool imu_init();
void imu_calibrate();
void imu_read();
float imu_get_omega();
void imu_set_radius(float);