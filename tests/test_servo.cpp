#include <iostream>
#include "servo.h"

using namespace std;

int main() {
    Servo servo(13);

    servo.init();

    servo.setPulseWidth(2500);
    servo.trim();
    
    int angle = servo.getAngle();
    cout << "Angle: " << angle << endl;

    servo.setAngle(120);
    servo.setAngle(180);
    servo.setAngle(0);

    return 0;
}