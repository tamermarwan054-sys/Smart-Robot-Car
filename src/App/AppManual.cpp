#include <Arduino.h>
#include "config.h"
#include "AppManual.h"
#include "HALmotor.h"

void executeCommand(char cmd, int spd) {
  switch (cmd) {
    case 'F': forward();       setSpeed(spd);                 break;
    case 'B': backward();      setSpeed(spd);                 break;
    case 'R': rightTurn();     setSpeed(spd);                 break;
    case 'L': leftTurn();      setSpeed(spd);                 break;
    case 'D': stopMotors();                                    break;
    case 'Q': forwardRight();  setMotorSpeeds(spd, spd / 2);  break;
    case 'E': forwardLeft();   setMotorSpeeds(spd / 2, spd);  break;
    case 'Z': backwardRight(); setMotorSpeeds(spd, spd / 2);  break;
    case 'C': backwardLeft();  setMotorSpeeds(spd / 2, spd);  break;
  }
}