#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "udp_multicast_client.h"
// #include "servo.h"
#include "servo_fk.h"


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
