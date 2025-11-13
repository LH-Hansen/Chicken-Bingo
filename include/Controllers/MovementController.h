#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <Arduino.h>
#include "Drivers/MotorDrivers.h"
#include "Drivers/SensorDrivers.h"
#include "Config.h"
#include "Settings.h"
#include "Drivers/WebDriver.h"

DCDriver motorR(L293D1_IN1, L293D2_IN2);
DCDriver motorL(L293D2_IN1, L293D2_IN2);
ServoDriver hatch(HATCH_IN, HATCH_OPEN, HATCH_CLOSED);
UltrasonicDriver rangeFinder(RANGEFINDER_TRIG, RANGEFINDER_ECHO);
DHTDriver climate(CLIMATE_IN, CLIMATE_TYPE);
WebDriver web(AP_SSID, AP_PASS);

class MovementController {
public:
  MovementController() {}

  void begin() {
    Serial.begin(115200);
    motorR.begin();
    motorL.begin();
    hatch.begin();
    climate.begin();
    web.begin();
  }

  bool move() {
    web.handle();

    float cm = rangeFinder.distanceCm(climate.readTemp());
    web.setDistance(cm);

    if (!web.running()) { motorStop(); _phaseActive = false; return false; }

    if (!_phaseActive) {
      _duration = random(TIME_MIN * 60000UL, TIME_MAX * 60000UL);
      _phaseEnd = millis() + _duration;
      _turning = false;
      _phaseActive = true;
      web.clearDone(); 
    }

    if (millis() >= _phaseEnd) {
      motorStop();
      hatch.open();
      _phaseActive = false;
      web.stop(); 
       web.markDone();
      return true;
    }

    if (cm >= 0 && cm > DISTANCE) {
      forward();
      return true;
    }

    if (cm >= 0) {
      if (!_turning) {
        _turnDir = random(0, 2);
        _turnUntil = millis() + random(1000UL, 2000UL);
        _turning = true;
      }
      if (millis() < _turnUntil) {
        if (_turnDir) turnRight(); else turnLeft();
      } else {
        _turning = false;
        motorStop();
      }
      return true;
    }

    motorStop();
    return true;
  }

private:
  void forward() { motorR.drive(); motorL.drive(); }
  void reverse() { motorR.reverse(); motorL.reverse(); }
  void turnRight() { motorR.reverse(); motorL.drive(); }
  void turnLeft() { motorR.drive(); motorL.reverse(); }
  void motorStop() { motorR.stop(); motorL.stop(); }

  unsigned long _duration = 0;
  unsigned long _phaseEnd = 0;
  unsigned long _turnUntil = 0;

  bool _phaseActive = false;
  bool _turning = false;
  uint8_t _turnDir = 0;
};

#endif
