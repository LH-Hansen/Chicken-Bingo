#ifndef MOTOR_DRIVERS_H
#define MOTOR_DRIVERS_H

#include <Arduino.h>
#include <Servo.h>

class DCDriver {
    public:
        explicit DCDriver(uint8_t in1, uint8_t in2): 
            _in1(in1), _in2(in2) {}
        void begin() { pinMode(_in1, OUTPUT); pinMode(_in2, OUTPUT); stop(); }
        void stop() { digitalWrite(_in1, LOW);  digitalWrite(_in2, LOW); }
        void drive() { digitalWrite(_in2, LOW);  digitalWrite(_in1, HIGH); }
        void reverse(){ digitalWrite(_in1, LOW);  digitalWrite(_in2, HIGH); }
    private:
        uint8_t _in1, _in2;
    };

class ServoDriver {
    public:
        explicit ServoDriver(uint8_t pin, uint8_t open_pos, uint8_t closed_pos)
            : _pin(pin), _open_pos(open_pos), _closed_pos(closed_pos) {}
        void begin() { _servo.attach(_pin); close(); }
        void open() { _servo.write(_open_pos); }
        void close() { _servo.write(_closed_pos); }
    private:
        uint8_t _pin, _open_pos, _closed_pos;
        ::Servo _servo;
};
#endif
