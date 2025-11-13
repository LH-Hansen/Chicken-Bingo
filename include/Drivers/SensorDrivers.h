#ifndef SENSOR_DRIVERS_H
#define SENSOR_DRIVERS_H

#include <Arduino.h>
#include <HCSR04.h>
#include <DHT.h>

class UltrasonicDriver {
public:
    explicit UltrasonicDriver(uint8_t trig, uint8_t echo)
        : _trig(trig), _echo(echo), _sensor(trig, echo) {}

    float distanceCm(float temp) { return _sensor.measureDistanceCm(temp); }

    float distanceMm(float temp) { return _sensor.measureDistanceCm(temp) * 10.0f; }

private:
    uint8_t _trig;
    uint8_t _echo;

    UltraSonicDistanceSensor _sensor;
};

class DHTDriver {
public:
    explicit DHTDriver(uint8_t pin, uint8_t type)
        : _pin(pin), _type(type), _dht(pin, type) {}

    void begin() { _dht.begin(); }

    float readTemp() { return _dht.readTemperature(); }

    float readHum() { return _dht.readHumidity(); }

private:
    uint8_t _pin;
    uint8_t _type;

    ::DHT _dht;
};

#endif
