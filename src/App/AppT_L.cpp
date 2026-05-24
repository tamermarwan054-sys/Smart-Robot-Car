#include <Arduino.h>
#include "config.h"
#include "HALmotor.h"
#include "AppManual.h"
#include "AppT_L.h"


bool stepGapActive = false;
unsigned long stepGapStart = 0;
void teachRepeatInit() {
  recordCount = 0;
  isRecording = false;
  isPlayback = false;
  lastCmd = 'D';
}

void saveStep() {
  if (recordCount >= MAX_STEPS) return;
  unsigned long duration = millis() - cmdStartTime;
  if (duration < 50) return;
  recording[recordCount].cmd = lastCmd;
  recording[recordCount].durationMs = duration;
  recordCount++;
}

void startRecording() {
  recordCount = 0;
  isRecording = true;
  lastCmd = 'D';
  cmdStartTime = millis();
}

void stopRecording() {
  if (lastCmd != 'D') saveStep();
  isRecording = false;
  stopMotors();
  Serial.print("REC:STOP:");
  Serial.println(recordCount);
}

void startPlayback() {
  if (recordCount == 0) return;
  isPlayback = true;
  playbackIndex = 0;
  stepGapActive = false;        
  stepGapStart = 0;             
  stepStartTime = millis();
  executeCommand(recording[0].cmd, 130);
}

void stopPlayback() {
  isPlayback = false;
  stopMotors();
  Serial.println("PB:DONE");
}

void handlePlayback() {
  if (!isPlayback) return;
  unsigned long now = millis();

  // ARE WE IN A GAP?
  if (stepGapActive) {
    if (now - stepGapStart >= STEP_GAP_MS) {
      stepGapActive = false;
      if (playbackIndex >= recordCount) {
        stopPlayback();
        return;
      }
      stepStartTime = now;
      executeCommand(recording[playbackIndex].cmd, 130);
    }
    return;  // still in gap, do nothing
  }

  // ARE WE RUNNING A STEP?
  if (now - stepStartTime >= recording[playbackIndex].durationMs) {
    stopMotors();           // stop between steps
    playbackIndex++;        // move to next step
    stepGapStart = now;     // start gap timer
    stepGapActive = true;   // enter gap mode
  }
}


void driveAndRecord(char cmd,int speedVal ) {
  if (isRecording && cmd != lastCmd) {
    if (lastCmd != 'D') saveStep();
    lastCmd = cmd;
    cmdStartTime = millis();
    executeCommand(cmd,130);
    return;
  }
  executeCommand(cmd,speedVal);
}