#include <Arduino.h>
#include "config.h"
#include "HALmotor.h"
#include "HALsensors.h"
#include "HALservo.h"
#include "AppAuto.h"

AutoState autoState = MOVING;
unsigned long timer = 0;
unsigned long turnDuration = 0;
int Rdist = 0;
int Ldist = 0;

void autonomousInit() {
  autoState = MOVING;
  myservo2.write(90);
}

void runAutonomous() {
  unsigned long now = millis();

  if (autoState == MOVING) {
    int dist = getFrontDistance();
    if (dist > 50) {
      forward(); setSpeed(80);
    } else {
      stopMotors();
      if (dist <= 30) { autoState = REVERSING; }
      else            { myservo2.write(0); autoState = SCAN_RIGHT; }
      timer = now;
    }
  }
  else if (autoState == REVERSING) {
    backward(); setSpeed(80);
    if (now - timer >= 400) {
      stopMotors(); myservo2.write(0);
      autoState = SCAN_RIGHT; timer = now;
    }
  }
  else if (autoState == SCAN_RIGHT) {
    if (now - timer >= 1000) {
      Rdist = getFrontDistance();
      myservo2.write(180);
      autoState = SCAN_LEFT; timer = now;
    }
  }
  else if (autoState == SCAN_LEFT) {
    if (now - timer >= 1000) {
      Ldist = getFrontDistance();
      myservo2.write(90);
      autoState = CENTERING; timer = now;
    }
  }
  else if (autoState == CENTERING) {
    if (now - timer >= 300) {
      if      (Rdist > Ldist) { rightTurn(); setSpeed(90); turnDuration = 500; }
      else if (Ldist > Rdist) { leftTurn();  setSpeed(90); turnDuration = 500; }
      else                    { rightTurn(); setSpeed(80); turnDuration = 1000; }
      autoState = TURNING; timer = now;
    }
  }
  else if (autoState == TURNING) {
    if (now - timer >= turnDuration) {
      stopMotors();
      Rdist = 0; Ldist = 0;
      autoState = MOVING;
    }
  }
}