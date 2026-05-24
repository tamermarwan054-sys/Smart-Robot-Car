#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "HALmotor.h"
#include "HALservo.h"
#include "HALsensors.h"
#include "HALbattery.h"
#include "AppManual.h"
#include "AppAuto.h"
#include "AppT_L.h"
#include "AppParking.h"




bool autonomousMode = false;
int speedVal = 150;
unsigned long lastBatteryTime = 0;

// Teach & Repeat variables
Step recording[MAX_STEPS];
int recordCount = 0;
bool isRecording = false;
bool isPlayback = false;
char lastCmd = 'D';
int playbackIndex = 0;
unsigned long stepStartTime = 0;
unsigned long cmdStartTime = 0;

// Parking variables
ParkState parkState = PARK_IDLE;
bool parkingMode = false;


void setup() {
  Serial.begin(9600);
  motorInit();
  sensorsInit();
  servoInit();
  autonomousInit();
  teachRepeatInit();
  parkingInit();
  checkBattery();
}


void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd >= '0' && cmd <= '9') { 
      speedVal = SPEED_MAP[cmd - '0']; 
      return; 
    }

    switch (cmd) {
      case 'A':
        if (!isRecording && !isPlayback && !parkingMode) {
          autonomousMode = !autonomousMode;
          if (!autonomousMode) stopMotors();
        }
        break;

      case 'K':
        if (!autonomousMode && !isRecording && !isPlayback) {
          if (!parkingMode) {
            parkingStart();
          } else {
            parkingMode = false;
            stopMotors();
            setServoAngle(SERVO_CENTER);
            Serial.println("PARK:CANCELLED");
          }
        }
        break;

      case 'P':
        if (!autonomousMode && !isPlayback && !parkingMode) {
          if (isRecording) stopRecording();
          else startRecording();
        }
        break;

      case 'V':
        if (!autonomousMode && !isRecording && !parkingMode) {
          if (isPlayback) stopPlayback();
          else startPlayback();
        }
        break;

      default:
        if (!autonomousMode && !isPlayback && !parkingMode)
          driveAndRecord(cmd, speedVal);
        break;
    }
  }

  if (autonomousMode) runAutonomous();
  if (parkingMode) handleParking();
  handlePlayback();

  if (millis() - lastBatteryTime >= BATTERY_INTERVAL_MS) {
    checkBattery();
    lastBatteryTime = millis();
  }
}