#ifndef APPT_L_H
#define APPT_L_H


#include "config.h"



extern Step recording[MAX_STEPS]; 
extern int recordCount;
extern bool isRecording;
extern bool isPlayback;
extern char lastCmd;
extern int playbackIndex;
extern unsigned long stepStartTime;
extern unsigned long cmdStartTime;

void teachRepeatInit();
void saveStep();
void startRecording();
void stopRecording();
void startPlayback();
void stopPlayback();
void handlePlayback();
void driveAndRecord(char cmd, int spd);

#endif