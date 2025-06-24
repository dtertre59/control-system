#include "coordinator.h"

#include <iostream>
#include <thread>
#include <chrono>

#define ADDR "224.0.0.1"
#define PORT 5007
#define INTERFACE "127.0.0.1"

#define PIN 13 // Pin GPIO 13
#define TRIM 0 // Trim 0

#define ACTUATOR_DISTANCE_MM 10

// typedef enum{
//     COPPER = 0,
//     ZINC,
//     BRASS,
//     PCB,
//     UNKNOWN,
// } MaterialType;

enum class MaterialType {
    COPPER = 0,
    ZINC,
    BRASS,
    PCB,
    UNKNOWN,
};

constexpr MaterialType DEFAULT_MATERIAL = MaterialType::COPPER;

typedef struct {
    MaterialType material;
    unsigned long timestamp_ms; // Timestamp in milliseconds
    float speed;
} Piece;

int calculateTimems(unsigned long init_timestamp_ms, float speed){

    float total_sleep_time_ms = (ACTUATOR_DISTANCE_MM / speed) * 1000.0f; // ms

    // Convert the init_timestamp (in ms) to a time_point
    chrono::system_clock::time_point init_time = chrono::system_clock::time_point(chrono::milliseconds(init_timestamp_ms));
    // Obtener duración desde el epoch del system_clock
    std::chrono::milliseconds init_timestamp_ms_2 = chrono::duration_cast<std::chrono::milliseconds>(init_time.time_since_epoch());

    chrono::system_clock::time_point time_now = chrono::system_clock::now();

    chrono::milliseconds fix_duration = chrono::duration_cast<chrono::milliseconds>(time_now - init_time);
    std::cout << "Fix duration in ms: " << fix_duration.count() << std::endl;

    // chrono::microseconds fix_duration_us = chrono::duration_cast<chrono::microseconds>(time_now - init_time);
    // std::cout << "Fix duration in us: " << fix_duration_us.count() << std::endl;

    int fixed_total_sleep_time_ms = static_cast<int>(total_sleep_time_ms) - fix_duration.count();
    // std::cout << "Fixed total sleep time in ms: " << fixed_total_sleep_time_ms << std::endl;

    return fixed_total_sleep_time_ms;
}


void worker(Coordinator* c, Piece piece, bool verbose = false) {
    if (verbose) {
        std::cout << "Verbose: " << verbose << endl;
    }
    
    int sleep_time_ms = calculateTimems(piece.timestamp_ms, piece.speed);

    if (verbose) {
        std::cout << "Sleep in ms: " << sleep_time_ms << endl;
    }

    if (verbose){
        std::cout << "Material id: " << static_cast<int>(piece.material) << std::endl;
        // std::cout << "Worker thread move servo to  " << c->_servo.getPulseWith() << " DONE" << std::endl;
    }

    // Sleep
    // sleep(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));

    if (piece.material == DEFAULT_MATERIAL) {
        // Move servo to position 1 (ACTIVE)
        c->_servo.setPulseWidth(1800);
    } else {
        // Move servo to position 0 (INACTIVE)
        c->_servo.setPulseWidth(1200);
    }
    return;
}


Coordinator::Coordinator(): _udp_multicast_client(ADDR, PORT, INTERFACE), 
                            _servo(PIN, TRIM) 
                            {

}


Coordinator::~Coordinator() {
    _servo.close();
}


bool Coordinator::run() {

    // Init servo
    _servo.init();

    _servo.setPulseWidth(1200);

    // Unirse al grupo multicast
    if (!_udp_multicast_client.joinGroup()) {
        cerr << "Error joining the multicast group" << endl;
        return 1;
    }

    // Recibir datos
    vector<uint8_t> data;
    Piece p;

    while (true) {
        std::cout << "Waiting for data..." << std::endl;
        data.clear();  // Limpiar el vector de datos
        data.resize(1024);  // Reservar espacio para los datos
        // Recibir el mensaje del grupo multicast
        if (_udp_multicast_client.receive(data, 1024)) {
            memcpy(&p, data.data(), sizeof(Piece));
            // Procesar datos recibidos
            // cout << "Data received: Material: " << p.material << "\tTimestamp: " // Para en enum clasico
            cout << "Data received: Material: " << static_cast<int>(p.material) << "\tTimestamp: " 
            << p.timestamp_ms << "\tSpeed " << p.speed << endl;
            
            // p.material = 1;
            // p.timestamp = 123456;

            // Start thread to control de piece (move servo when it is time to do it)
            // std::thread t(worker_1);
            std::thread t(worker, this, p, true); // Aquí pasas 1 y 1 como parámetros
            // Separar el hilo para que continúe ejecutándose en segundo plano
            t.detach();
            
        }
    }
}
