#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "HALservo.h"

Servo myservo;
Servo myservo2;

void servoInit() {
  myservo.attach(SERVO_PIN);  // to the pin of the servo 
  myservo.write(SERVO_CENTER);  // write the angle of the servo 0<angle >180
  myservo2.attach(servo2);
  myservo2.write(SERVO_CENTER);
}

void setServoAngle(int angle) { myservo.write(angle); }