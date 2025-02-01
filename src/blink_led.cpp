

/*
* Conexion con un Pin GPIO de la raspberry pi
* Se utiliza la libreria pigpio
* Para que funcione correctamente es necesario que NO este corriendo el demonio pigpiod.
*/

#include <iostream>
#include <pigpio.h>
# include <unistd.h>    // for sleep()

using namespace std;

int main() {

    // Print the pigpio lib version
    cout << "Using pigpio version " << gpioVersion() <<endl;
    cout << "Running on " << gpioHardwareRevision() <<endl;

    // Initialize the pigpio lib
    if (gpioInitialise() < 0) {
        cerr << "Error when pigpio initialize" << endl;
        return 0;
    }

    // Define Pins
    int ledPin = 26;

    cout << "Configured led on " << ledPin << endl;
    
    gpioSetMode(ledPin, PI_OUTPUT);

    for (int i = 0; i < 10; i++) {
        gpioWrite(ledPin, 1);
        cout << "Led ON" << endl;
        sleep(1);
        gpioWrite(ledPin, 0);
        cout << "Led OFF" << endl;
        sleep(1);
    }
    
    gpioWrite(ledPin, 0);

    gpioTerminate();
    return 0;
}