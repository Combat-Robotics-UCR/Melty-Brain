#include <Arduino.h>
#include "sbus.h"
#include "Radio.h"
#include "Config.h"

const int SBUS_MIN = 172;
const int SBUS_MID = 992;
const int SBUS_MAX = 1811;

static bfs::SbusRx sbus(&Serial2, RX_PIN, -1, true);
static bfs::SbusData data;
static unsigned long last_frame_time = 0;

void radio_init() {
  sbus.Begin();
}

void radio_update() {
  if (sbus.Read()) {
    data = sbus.data();
    last_frame_time = millis();
  }
}

bool radio_connected() {
  bool recent = (millis() - last_frame_time) < Failsafe_Ms;

  return recent && !data.failsafe;
}

float radio_throttle() {
  float t = (data.ch[Throttle] - SBUS_MIN) / float(SBUS_MAX - SBUS_MIN);
  return constrain(t, 0.0, 1.0);
}

float radio_steer_x() {
  float x = (data.ch[Steer_LeftRight] - SBUS_MID) / float(SBUS_MAX - SBUS_MID);
  return constrain(x, -1.0, 1.0);
}

float radio_steer_y() {
  float y = (data.ch[Steer_UpDown] - SBUS_MID) / float(SBUS_MAX - SBUS_MID);
  return constrain(y, -1.0, 1.0);
}
