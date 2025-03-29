#include "coordinator.h"

#include <iostream>
#include <thread>

#define ADDR "224.0.0.1"
#define PORT 5007
#define INTERFACE "127.0.0.1"

#define PIN 18 // Pin GPIO 18
#define TRIM 0 // Trim 0


typedef struct {
    int material;
    int timestamp;
} Piece;


void worker(Coordinator* c, int state, int timestamp) {

    if (state == 1) {
        // Move servo to position 1
        c->_servo.setPulseWidth(1800);
    } else {
        c->_servo.setPulseWidth(1000);
    }

    std::cout << "Worker thread move servo to  " << c->_servo.getPulseWith() << " DONE" << std::endl;

    return;
}


Coordinator::Coordinator(): _udp_multicast_client(ADDR, PORT, INTERFACE), 
                            _servo(PIN, TRIM) 
                            {

}


Coordinator::~Coordinator() {

}


bool Coordinator::run() {

    // Init servo
    _servo.init();

    // Unirse al grupo multicast
    if (!_udp_multicast_client.joinGroup()) {
        cerr << "Error al unirse al grupo multicast" << endl;
        return 1;
    }

    // Recibir datos
    std::cout << "Esperando datos..." << std::endl;
    // Recibir datos
    vector<uint8_t> data;
    Piece p;

    while (true) {
        std::cout << "Esperando datos..." << std::endl;
        data.clear();  // Limpiar el vector de datos
        data.resize(1024);  // Reservar espacio para los datos
        // Recibir el mensaje del grupo multicast
        if (_udp_multicast_client.receive(data, 1024)) {
            memcpy(&p, data.data(), sizeof(Piece));
            // Procesar datos recibidos
            cout << "Datos recibidos: Material: " << p.material << "\tTimestamp: " << p.timestamp << endl;
            
            // p.material = 1;
            // p.timestamp = 123456;

            // Start thread to control de piece (move servo when it is time to do it)
            // std::thread t(worker_1);
            std::thread t(worker, this, p.material, p.timestamp); // Aquí pasas 1 y 1 como parámetros
            // Separar el hilo para que continúe ejecutándose en segundo plano
            t.detach();
            
        }
    }
}
