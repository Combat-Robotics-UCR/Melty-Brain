#include "motor.h"

const int PWM_PIN = 13;
const int MOTOR_PIN = 21;

volatile unsigned long riseTime = 0; //
volatile unsigned long widthUs = 0; //

motor test;
bool update = false;

void IRAM_ATTR func() {  //
  unsigned long now = micros();  //
  if (digitalRead(PWM_PIN) == HIGH) { //
    riseTime = now; // 
  } else { //
    widthUs = now - riseTime; //
    update = true; //
  } //
} //

void setup() {
  Serial.begin(115200);

  test.init(MOTOR_PIN);

  pinMode(PWM_PIN, INPUT); //
  attachInterrupt(digitalPinToInterrupt(PWM_PIN), func, CHANGE); //
}

void loop() {  
  if (channel.update){
    data = channel.getdata
  }
}