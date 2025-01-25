

/*
* Conexion con un Pin GPIO de la raspberry pi
* Se utiliza la libreria pigpio , el modulo pigpiod_if2 el cual nos permite conectarnos al proceso demonio (que debe estar funcionando previameinte)
* Esto habilita la posibilidad de connectarnos por red a otros daemons. En el start se configura la ip y el port
* Como estamos en local lo hemos dejado en nullptr
*/

#include <iostream>
#include <pigpiod_if2.h>
#include <thread>
# include <unistd.h>    // for sleep()

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
    int ledPin = 26;

    cout << "Configuring led on " << ledPin << endl;
    
    set_mode(gpioHandle, ledPin, PI_OUTPUT);

    for (int i = 0; i < 10; i++) {
        gpio_write(gpioHandle, ledPin, 1);
        cout << "Led ON" << endl;
        sleep(1);
        gpio_write(gpioHandle, ledPin, 0);
        cout << "Led OFF" << endl;
        sleep(1);
    }

    // Close pigpio daemon connection 
    pigpio_stop(gpioHandle);

    return 0;
}