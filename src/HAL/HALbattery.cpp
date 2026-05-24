#include <Arduino.h>
#include "config.h"
#include "HALbattery.h"

int getBatteryPercent() {
  int   reading = analogRead(BATTERY_PIN);
  float voltage = reading * (5.0 / 1023.0) * 4.0; //0--1023 
  float percent = (voltage / 12.0) * 100.0;
  if (percent < 0)   percent = 0; // in case of bad reading 
  if (percent > 100) percent = 100;
  return (int)percent;
}

void checkBattery() {
  Serial.print("B:");
  Serial.println(getBatteryPercent());
}