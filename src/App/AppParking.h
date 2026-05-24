#ifndef APPPARKING_H
#define APPPARKING_H

#include "config.h"

extern ParkState parkState;
extern bool parkingMode;

void parkingInit();
void parkingStart();
void handleParking();

#endif