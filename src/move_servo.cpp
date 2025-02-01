

/*
* Conexion con un Pin GPIO de la raspberry pi
* Se utiliza la libreria pigpio , el modulo pigpiod_if2 el cual nos permite conectarnos al proceso demonio (que debe estar funcionando previameinte)
* Esto habilita la posibilidad de connectarnos por red a otros daemons. En el start se configura la ip y el port
* Como estamos en local lo hemos dejado en nullptr
*/

#include <iostream>
#include <pigpiod_if2.h>
#include <thread>
#include <unistd.h>    // for sleep()

using namespace std;

int main() {

    // Connect to the local pigpio daemon
    cout << "Connecting to pigpio daemon ...";
    int gpioHandle = pigpio_start(nullptr, nullptr);
    if (gpioHandle < 0) {
        cerr << "ERROR" << endl;
        cerr << "Returned error = " << gpioHandle << endl;
        return -1;
    }
    cout << "SUCCESS" << endl;

    // Print the pigpio lib version
    cout << "Using pigpio version " << get_pigpio_version(gpioHandle) <<endl;
    cout << "Running on " << get_hardware_revision(gpioHandle) <<endl;


    // Define Pins
    int SERVO_PIN = 13;
    int angle;

    cout << "Configuring servo on " << SERVO_PIN << endl;
    
    set_mode(gpioHandle, SERVO_PIN, PI_OUTPUT);

    while (true) {
        cout << "Set angle: ";
        cin >> angle;

        // 500 = -90 and 2500 = 90 -> 1500 = 0
        if (angle < 0 || angle > 2500) {
            cout << "Invalid angle" << endl;
            continue;
        }
        // Set servo pulsewidth
        set_servo_pulsewidth(gpioHandle, SERVO_PIN, angle);
    }

    // Close pigpio daemon connection 
    pigpio_stop(gpioHandle);

    return 0;
}