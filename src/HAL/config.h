#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 4;
const int IN4 = 2;
const int ENA = 3;
const int ENB = 5;

const int TRIG_FRONT  = 6;
const int ECHO_FRONT  = A1;
const int TRIG_RIGHT  = A2;
const int ECHO_RIGHT  = 10;
const int TRIG_REAR   = 12;
const int ECHO_REAR   = 13;
const int servo2      = 11;
const int SERVO_PIN   = 9;
const int BATTERY_PIN = A0;

const int SPEED_MAP[10] = {0, 28, 56, 85, 113, 142, 170, 198, 226, 255}; // array of speed 
const int PARK_SPEED    = 80;
const int SERVO_CENTER  = 90;
const int SERVO_LEFT_60 = 60; // the angle of the back park 

const unsigned long BATTERY_INTERVAL_MS = 3000;
const unsigned long PARK_STOP_MS        = 400; // the car stop for 400 ms 
const unsigned long TURN_45_MS          = 350; // the time car move right or left to rotate 45 degree 
const unsigned long TURN_STRAIGHTEN_MS  = 300; // the time car take to make the car straght again 
const unsigned long REVERSE_TIMEOUT_MS  = 5000;
const unsigned long FORWARD_TIMEOUT_MS  = 5000;
const unsigned long STATE_CHANGE_DELAY  = 100;
const unsigned long GAP_CONFIRM_TIME    = 200; // to make sure that gap is enough to park in 
const unsigned long STOP_AFTER_TURN_MS  = 300;

const float GAP_THRESHOLD_CM      = 10.0;
const float RETURN_TOLERANCE_CM   = 20.0;
const float MAX_CAR_DISTANCE_CM   = 60.0;
const float REAR_STOP_DISTANCE    = 25.0;
const float FRONT_SAFETY_DISTANCE = 25.0;
const unsigned long STEP_GAP_MS = 200;  
extern bool stepGapActive;              
extern unsigned long stepGapStart;


const int STOP_CM    = 40;
const int REVERSE_CM = 20;
const int MAX_STEPS  = 100;

enum AutoState {
  MOVING, 
  REVERSING, 
  SCAN_RIGHT, 
  SCAN_LEFT, 
  CENTERING, 
  TURNING
};

enum ParkState {
  PARK_IDLE, 
  PARK_SCAN_BOX1, 
  PARK_GAP_TRANSITION, 
  PARK_SCAN_GAP,
  PARK_STOP_1, 
  PARK_ENTRY_TURN, 
  PARK_STOP_2, 
  PARK_REVERSE,
  PARK_STOP_3, 
  PARK_STRAIGHTEN_TURN, 
  PARK_STOP_4, 
  PARK_CENTER_FORWARD, 
  PARK_DONE
};

struct Step {
  char cmd;
  unsigned long durationMs;
};

#endif