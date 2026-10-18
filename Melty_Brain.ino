#include "Melty.h"

Melty melty;

void setup() {
  melty.init();
  melty.error_handler();
}

void loop() {
  melty.read_IMU();

  melty.update_heading();

  melty.pulse_LED();

  melty.write_SD_card();

  melty.error_handler();
}

// ------------------------------------------------------ //
/*
Error log:
  - need performance characterization of gyro and accelerometer independently
  - maybe due to omega inherent error

  *** noticed IMU stops logging data, this could be cause of errors --> switched to SPI wiring TBD if that will solve issue
*/