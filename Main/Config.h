#pragma once

// LEDs
const int LED_PIN = 27;
const float BLINK_WIDTH = 0.5;  // how wide the flash in (radians)
const float FORWARD = 0.0;      // front position

//---------------------------------------------------------------

//MPU
const int SDA_PIN = 23;
const int SCL_PIN = 22;

//MPU Limits
float IMU_RADIUS = 0.057;  //sensor distance from spin center (meters)
const float GYRO_LIMIT = 1.0;   // if spins faster than this go to spinning force thingy
//---------------------------------------------------------------

//ESCs signal wires
const int MOTOR1 = 21;
const int MOTOR2 = 32;

//---------------------------------------------------------------

//Reciever pins
const int RC1 = 12;
const int RC2 = 13;
const int RC3 = 15;
const int RC4 = 33;
