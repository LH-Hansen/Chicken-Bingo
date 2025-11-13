#pragma once

#include <Arduino.h>   // defines uint8_t and other types
#include "DHT.h"

constexpr uint8_t TIME_MIN = 7;
constexpr uint8_t TIME_MAX = 14;

constexpr uint8_t DISTANCE = 10;

constexpr unsigned long TURN_VALUE = 3000;

constexpr uint8_t HATCH_OPEN = 180;
constexpr uint8_t HATCH_CLOSED = 0;

constexpr uint8_t CLIMATE_TYPE = DHT11;

constexpr const char* AP_SSID = "D1_Mini_AP";
constexpr const char* AP_PASS = "P@ssw0rd";
