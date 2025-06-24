#ifndef SERVO_FK_H
#define SERVO_FK_H

#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

/*
* Servo FAKE class

This class simulates a servo motor using a fake implementation.

*/

class Servo {

    public:
        Servo(int pin, int trim = 0);
        ~Servo();
        int init();
        int getPulseWith();
        int setPulseWidth(int pulseWidth);
        float getAngle();
        int setAngle(float angle);
        int close();
        int trim();
        

    private:
        const int _pin;
        bool _isInitialize;
        int _trim;
        int _pulseWidth; // 0 == off || 500 > pulseWidth < 2500
        int _gpioHandle;
};

#endif // SERVO_FK_src/servo.cpp
