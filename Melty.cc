#include "pins_arduino.h"
#include "Melty.h"

void Melty::init() {
  // Start Serial, I2C, FIXME: ADD SPI, and LED output
  Serial.begin(115200);
  delay(100);

  pinMode(_SD_CS, OUTPUT);    digitalWrite(_SD_CS, HIGH);
  pinMode(_IMU_CS, OUTPUT); digitalWrite(_IMU_CS, HIGH);
  delay(100);
  
  SPI.begin(_SPI_SCK, _SPI_MISO, _SPI_MOSI);
  delay(100);

  // Initialize LEDs
  pinMode(_LED_PIN, OUTPUT);
  digitalWrite(_LED_PIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  // Verify IMU functionality
  if (!_imu.begin_SPI(_IMU_CS, _IMU_INT, &SPI)) {
    Errors[0] = 1;
  }
  delay(100);

  // Verify SD card functionality
  if (!SD.begin(_SD_CS, SPI)) {
    Errors[1] = 1;
  }
  delay(100);

  // Enable IMU sensors
  _imu.enableReport(SH2_GYROSCOPE_CALIBRATED);
  _imu.enableReport(SH2_ACCELEROMETER);

  // Write CSV header
  appendFile(SD, "/imu_data.txt", "time_us,heading,omega\n");
  
  // Pulse LED to indicate robot is about to start
  for (unsigned i = 0; i < 10; i++) {
    digitalWrite(_LED_PIN, HIGH);
    delay(100);
    digitalWrite(_LED_PIN, LOW);
    delay(100);
  }

  Serial.println("-------------------------");
  
  _time = micros();
}

void Melty::read_IMU() {
  // Check for a sensor reading
  if(_imu.getSensorEvent(&_sensor)){
    if(_sensor.sensorId == SH2_GYROSCOPE_CALIBRATED) {
      _gyro_z = _sensor.un.gyroscope.z;
      Serial.println(_gyro_z);
    }
    if(_sensor.sensorId == SH2_ACCELEROMETER) {
      _ax = _sensor.un.accelerometer.x;
      _ay = _sensor.un.accelerometer.y;
    }
  }

  // Update angular velocity. 25 is the gyroscope's Rad/s limit
  if(abs(_gyro_z) < 25.0) {
    _omega = _gyro_z;
  } else {
    float accel = sqrt(_ax * _ax + _ay * _ay);
    _omega = sqrt(accel / _radius);
  }

  // FIXME: add error handling logic here if possible
}

void Melty::pulse_LED() {
  if (abs(_heading) < _blink_range) {
    digitalWrite(_LED_PIN, HIGH);
  } else {
    digitalWrite(_LED_PIN, LOW);
  }
}

float Melty::update_heading() {
  unsigned long curr_time = micros();
  _heading += _omega * ((curr_time - _time) / 1e6);
  _heading = fmod(_heading, 2 * PI);

  _time = curr_time;

  return _heading;
}

void Melty::error_handler() {
  if (Errors[0]) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("IMU.begin failure");
    while (1) {
      for (unsigned i = 0; i < 2; i++) {
        digitalWrite(_LED_PIN, HIGH);
        delay(100);
        digitalWrite(_LED_PIN, LOW);
        delay(100);
      }
      delay(1000);
    }
  } 
  if (Errors[1]) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Failed to mount SD card");
    while (1) {
      for (unsigned i = 0; i < 3; i++) {
        digitalWrite(_LED_PIN, HIGH);
        delay(100);
        digitalWrite(_LED_PIN, LOW);
        delay(100);
      }
      delay(1000);
    }
  }
  if (Errors[2]) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Failed to open SD file for appending");
    while (1) {
      for (unsigned i = 0; i < 4; i++) {
        digitalWrite(_LED_PIN, HIGH);
        delay(100);
        digitalWrite(_LED_PIN, LOW);
        delay(100);
      }
      delay(1000);
    }
  }
  if (Errors[3]) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("SD file append Failed");
    while (1) {
      for (unsigned i = 0; i < 5; i++) {
        digitalWrite(_LED_PIN, HIGH);
        delay(100);
        digitalWrite(_LED_PIN, LOW);
        delay(100);
      }
      delay(1000);
    }
  }

  // if (Errors[X]) {}
}

void Melty::appendFile(fs::FS &fs, const char *path, const char *message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Errors[2] = 1;  // Failed to open SD file for appending
    return;
  }
  if (!file.print(message)) {
    Errors[3] = 1;  // SD file append Failed
    return;
  }
  file.close();
}

void Melty::write_SD_card() {
  char row[64];
  sprintf(row, "%lu,%.4f,%.4f\n", micros(), _heading, _omega);
  appendFile(SD, "/imu_data.txt", row);
}
