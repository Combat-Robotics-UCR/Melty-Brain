# Melty Brain Code


The LED will blink in recognizable patterns at rest. The ESP32 onboard LED will turn on to indicate an error has been detected
LED blinking chart:
Error Index | Blinks per cycle | Error
0           | 2                | IMU failed to connect
1           | 3                | Failed to mount SD card
2           | 4                | Failed to open SD file for appending
3           | 5                | SD file append Failed