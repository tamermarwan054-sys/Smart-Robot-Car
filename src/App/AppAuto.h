#ifndef APPAUTO_H
#define APPAUTO_H


#include "config.h"
#include "servo.h"
extern Servo myservo2;
extern AutoState autoState;
extern unsigned long timer;
extern unsigned long turnDuration;
extern int Rdist;
extern int Ldist;

void autonomousInit();
void runAutonomous();

#endif