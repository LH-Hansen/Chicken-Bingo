#pragma once

#include <Arduino.h>  

// Motor pins
constexpr uint8_t L293D1_IN1 = D3;
constexpr uint8_t L293D1_IN2 = D4;
constexpr uint8_t L293D2_IN1 = D6;
constexpr uint8_t L293D2_IN2 = D7;

// Ultrasonic pins
constexpr uint8_t RANGEFINDER_TRIG = D2;
constexpr uint8_t RANGEFINDER_ECHO = D1;

// Servo pin
constexpr uint8_t HATCH_IN = D5;

// DHT
constexpr uint8_t CLIMATE_IN = D8;
