#ifndef HALMOTOR_H
#define HALMOTOR_H

void motorInit();
void stopMotors();
void setSpeed(int s);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
void forward();
void backward();
void rightTurn();
void leftTurn();
void forwardRight();
void forwardLeft();
void backwardRight();
void backwardLeft();

#endif