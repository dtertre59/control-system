#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "udp_multicast_client.h"

#ifdef __linux__
    #include "servo.h"
#elif  defined(__APPLE__)
    #include "servo_fk.h"
#else
    #error "Unsupported platform. Please implement the Servo class for your platform."
#endif

class Coordinator {
    public:
        Coordinator();

        ~Coordinator();

        bool run();

        // static void worker(Coordinator* c, int state, int timestamp);

    public:
        UdpMulticastClient _udp_multicast_client;

        Servo _servo;  // Servo object

};


#endif // COORDINATOR_H
