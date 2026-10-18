#include <type_traits>
#include <stdint.h>
#ifndef MELTY_H
#define MELTY_H

#include <Adafruit_BNO08x.h>
#include "esp32-hal.h"
#include "pins_arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class Melty {
  private:
    // Pinout
    const uint8_t _LED_PIN = 25;

    const uint8_t _SPI_MOSI = 23;
    const uint8_t _SPI_MISO = 19;
    const uint8_t _SPI_SCK = 18;

    const uint8_t _IMU_CS = 5;
    const uint8_t _IMU_INT = 4;
    const uint8_t _IMU_RESET = 15;

    const uint8_t _SD_CS = 26;

    // Peripheral variables
    Adafruit_BNO08x _imu = Adafruit_BNO08x(15); // 15 is _IMU_RESET pin
    sh2_SensorValue_t _sensor;

    // IMU data variables
    float _gyro_z = 0;
    float _ax = 0, _ay = 0;

    // Property variables
    unsigned long _time = 0;
    float _heading = 0;
    float _omega = 0;

    // Constant variables
    const float _radius = 0.037282; // meters
    const float _blink_range = 0.5; //RAD

    // Error variable to track failures
    bool Errors[4] = {0 , 0, 0, 0};

  public:
    // Initialization functions
    void init();

    // Configuration funcitons
    // void config_radius(float radius_lower, float radius_upper); // Used to set a correct radius
    // void config_LED();

    // Peripheral access functions
    void read_IMU();  // Updates object's imu data
    void pulse_LED(); // Pulses LED once per rotation
    void write_SD_card(); // Writes heading and omega from gyro or accelerometer

    // Internal data functions
    float update_heading(); // Updates heading using currently available IMU data

    // Error handling functions
    void error_handler(); // Sets LED blinking pattern if errors occur SEE README FOR REFERENCE

  private:
    // Helper functions
    void appendFile(fs::FS &, const char *, const char *);  // Appends content into an SD card file
};

#endif // MELTY_H
