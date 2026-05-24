#include <Arduino.h>
#include "config.h"
#include "HALsensors.h"

void sensorsInit() {
  pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_REAR,  OUTPUT); pinMode(ECHO_REAR,  INPUT);
}

float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.0343 / 2.0;
}

float getFrontDistance() { return readUltrasonic(TRIG_FRONT, ECHO_FRONT); }
float getRightDistance() { return readUltrasonic(TRIG_RIGHT, ECHO_RIGHT); }
float getRearDistance()  { return readUltrasonic(TRIG_REAR,  ECHO_REAR);  }