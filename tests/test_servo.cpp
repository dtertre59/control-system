#include <iostream>
#include "servo.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool t_value = false;

    for (int i = 0; i < argc; i++){
        string arg = argv[i];
        if (arg == "-t") {
            t_value = true;
            break;
        }
    }

    Servo servo(13);

    servo.init();

    // Trim
    if (t_value) {
        servo.trim();
        return 0;
    }

    // Normal mode

    servo.setPulseWidth(2500);
    
    int angle = servo.getAngle();
    cout << "Angle: " << angle << endl;

    servo.setAngle(120);
    servo.setAngle(180);
    servo.setAngle(0);

    return 0;
}