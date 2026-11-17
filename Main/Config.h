#pragma once

// LEDs
const int LED_PIN = 27;
const int ERROR_LED = 13;
const float BLINK_WIDTH = 0.5;  // how wide the flash in (radians)
const float FORWARD = 0.0;      // front position

//---------------------------------------------------------------

//MPU
const int SDA_PIN = 23;
const int SCL_PIN = 22;

//MPU Limits
const float IMU_RADIUS = 0.057;  //sensor distance from spin center (meters)
const float GYRO_LIMIT = 30.0;   // if spins faster than this go to spinning force thingy
//---------------------------------------------------------------

//ESCs signal wires
const int MOTOR1 = 21;
const int MOTOR2 = 32;

//Motor constants
const int ESC_MIN = 1000;
const int ESC_MAX = 2000;
const int ESC_ARM = 2000;

//---------------------------------------------------------------

//Reciever
const int RX_PIN = 16;

//Radio
const int Steer_LeftRight = 0;
const int Steer_UpDown = 1;
const int Throttle = 2;
const int Failsafe_Ms = 250;  //if no signal after x_ms everything stops
const float DRIVE_STRENGTH = 0.3;

//driving
const float THROTTLE_DEADZONE = 0.05;
const float STICK_DEADZONE = 0.15;
const float DRIVE_BOOST = 0.2;
