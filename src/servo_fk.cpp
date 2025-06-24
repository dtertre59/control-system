#include "servo_fk.h"


Servo::Servo(int pin, int trim): _pin(pin), _trim(trim) {
    _isInitialize = false;
    _pulseWidth = 0;
}


Servo::~Servo() {
    if (_isInitialize == true) {
        close();
    }
}


int Servo::init() {

    cout << "\n---------- Init FAKE Servo ----------\n" << endl;

    cout << "Connecting to FAKE pigpio daemon ... ";

    _isInitialize = true;
    _gpioHandle = 0; // Simulated handle

    cout << "SUCCESS" << endl;

    return 0;
}


int Servo::close() {
    cout << "FAKE Servo is clossing ... "; 

    _isInitialize = false;
    _gpioHandle = -1; // Simulated handle

    cout << "SUCCESS" << endl;

    return 0;
}


int Servo::getPulseWith() {
    if (!_isInitialize) {
        cout << "Servo is not initialized" << endl;
        return -1;
    }

    return _pulseWidth;
}


int Servo::setPulseWidth(int pulseWidth) {

    if (!_isInitialize) {
        cout << "Servo is not initialized" << endl;
        return -1;
    }

    if (pulseWidth < 500 || pulseWidth > 2500) {
        cout << "Servo PulseWidth must be between 500 and 2500" << endl;
        return -1;
    }

    if (_pulseWidth == pulseWidth) {
        cout << "Servo is in that position" << endl;
        return 0;
    }

    cout << "Servo is moving to " << pulseWidth << " ... " << flush;

    // wait estimated time
    sleep(1); // 500 -> 2500 time

    cout << "SUCCESS" << endl;

    _pulseWidth = pulseWidth;

    return 0;
}


float Servo::getAngle() {
    if (!_isInitialize) {
        cout << "Servo is not initialized" << endl;
        return -1;
    }
    float angle;

    int trimmedPulseWidth = _pulseWidth + _trim;


    angle = ((trimmedPulseWidth - 500) * 180) / 2000;

    return angle;
}

int Servo::setAngle(float angle) {
    if (!_isInitialize) {
        cout << "Servo is not initialized" << endl;
        return -1;
    }

    int pulseWidth = (((angle * 2000) / 180) + 500 - _trim);

    if (pulseWidth > 200 && pulseWidth < 500) {
        cout << "Pulse width is smaller than 500: " << pulseWidth << endl;
        pulseWidth = 500;
    }

    if (pulseWidth > 2500 && pulseWidth < 2800) {
        cout << "Pulse width is bigger than 2500: " << pulseWidth << endl;
        pulseWidth = 2500;
    }

    return setPulseWidth(pulseWidth);
}



int Servo::trim() {
    if (!_isInitialize) {
        cout << "Servo is not initialized" << endl;
        return -1;
    }

    cout << endl;
    cout << " ---------- Trimming mode ----------" << endl << endl;
    cout << "   - Try to put your servo in the middle angle\n";
    cout << "   - Press 0 to end trimming" << endl << endl;

    int flag = 1;
    int pulseWidth = 1500;

    setPulseWidth(pulseWidth);

    while (flag != 0) {
        cout << "Set pulsewith: ";
        cin >> flag;
        if (flag == 0) {
            break;
        }else {
            pulseWidth = flag;
        }
        setPulseWidth(pulseWidth);
    }
    _trim = 1500 - _pulseWidth;
    cout << "Trim: " << _trim << endl;
    cout << "Trim mode closed" << endl<< endl;
    return 0;
}
