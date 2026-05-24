#include <Arduino.h>
#include "config.h"
#include "HALmotor.h"
#include "HALsensors.h"
#include "HALservo.h"
#include "AppParking.h"

unsigned long parkActionTime = 0;
float parkBaseline = -1.0;
bool box1Detected = false;
unsigned long box1StartTime = 0;
unsigned long gapStartTime = 0;
float box1LengthCm = 0;
float gapLengthCm = 0;
unsigned long stateChangeTime = 0;
unsigned long gapConfirmStart = 0;
bool gapConfirming = false;

void parkingInit() {
  parkState = PARK_IDLE;
  parkingMode = false;
  parkBaseline = -1.0;
  box1Detected = false;
  gapConfirming = false;
}

void parkingStart() {
  parkingMode = true;
  parkState = PARK_SCAN_BOX1;
  Serial.println("PARK:START");
}

void handleParking() {
  unsigned long now = millis();
  float rightDist = getRightDistance();
  float rearDist = getRearDistance();

  switch (parkState) {

    case PARK_SCAN_BOX1:
      forward(); setSpeed(PARK_SPEED);
      if (!box1Detected && rightDist < MAX_CAR_DISTANCE_CM && rightDist < 999.0) {
        parkBaseline = rightDist; box1StartTime = now; box1Detected = true;
      }
      if (box1Detected && rightDist > parkBaseline + GAP_THRESHOLD_CM) {
        if (!gapConfirming) {
          gapConfirmStart = now; gapConfirming = true;
        } else if (now - gapConfirmStart >= GAP_CONFIRM_TIME) {
          box1LengthCm = (now - box1StartTime) * 0.04279;
          gapStartTime = now;
          gapConfirming = false;
          stateChangeTime = now;
          parkState = PARK_GAP_TRANSITION;
        }
      } else gapConfirming = false;
      break;

    case PARK_GAP_TRANSITION:
      forward(); setSpeed(PARK_SPEED);
      if (now - stateChangeTime >= STATE_CHANGE_DELAY) parkState = PARK_SCAN_GAP;
      break;

    case PARK_SCAN_GAP:
      forward(); setSpeed(PARK_SPEED);
      if (rightDist <= parkBaseline + RETURN_TOLERANCE_CM && rightDist < 999.0 && rightDist > 0) {
        gapLengthCm = (now - gapStartTime) * 0.04279;
        stopMotors(); parkActionTime = now; parkState = PARK_STOP_1;
      } else if (now - gapStartTime > 5000) {
        stopMotors(); parkingMode = false; parkState = PARK_IDLE;
        Serial.println("PARK:CANCELLED");
      }
      break;

    case PARK_STOP_1:
  if (now - parkActionTime >= PARK_STOP_MS) {
    parkState = PARK_ENTRY_TURN;
    parkActionTime = now;  
  }
  break;

    case PARK_ENTRY_TURN:
      leftTurn();
      setSpeed(PARK_SPEED);
      if (now - parkActionTime >= TURN_45_MS) {
        stopMotors(); parkActionTime = now; parkState = PARK_STOP_2;
      }
      break;

    case PARK_STOP_2:
      if (now - parkActionTime >= PARK_STOP_MS) {
        setServoAngle(SERVO_LEFT_60); 
        parkActionTime = now; parkState = PARK_REVERSE;
      }
      break;

    case PARK_REVERSE:
      backward(); setSpeed(PARK_SPEED);
      if (rearDist <= REAR_STOP_DISTANCE && rearDist > 0 && rearDist < 999.0) {
        stopMotors(); setServoAngle(SERVO_CENTER);
        parkActionTime = now; parkState = PARK_STOP_3;
      } else if (now - parkActionTime > REVERSE_TIMEOUT_MS) {
        stopMotors(); setServoAngle(SERVO_CENTER);
        parkingMode = false; parkState = PARK_IDLE;
        Serial.println("PARK:CANCELLED");
      }
      break;

    case PARK_STOP_3:
      if (now - parkActionTime >= PARK_STOP_MS) {
        parkActionTime = now; parkState = PARK_STRAIGHTEN_TURN;
      }
      break;

    case PARK_STRAIGHTEN_TURN:
      rightTurn(); setSpeed(PARK_SPEED);
      if (now - parkActionTime >= TURN_STRAIGHTEN_MS) {
        stopMotors(); parkActionTime = now; parkState = PARK_STOP_4;
      }
      break;

    case PARK_STOP_4:
      if (now - parkActionTime >= PARK_STOP_MS) {
        parkActionTime = now; parkState = PARK_CENTER_FORWARD;
      }
      break;

    case PARK_CENTER_FORWARD: {
      forward(); setSpeed(PARK_SPEED);
      float f = getFrontDistance();
      float r = getRearDistance();
      if (f > 0 && f < 999.0 && r > 0 && r < 999.0 && abs(f - r) <= 10.0) {
        stopMotors(); Serial.println("PARK:DONE");
        parkingMode = false; parkState = PARK_DONE;
      } else if (f > 0 && f < FRONT_SAFETY_DISTANCE) {
        stopMotors(); Serial.println("PARK:DONE");
        parkingMode = false; parkState = PARK_DONE;
      } else if (now - parkActionTime > FORWARD_TIMEOUT_MS) {
        stopMotors(); Serial.println("PARK:CANCELLED");
        parkingMode = false; parkState = PARK_IDLE;
      }
      break;
    }

    case PARK_DONE:
    case PARK_IDLE:
      break;
  }
}