#ifndef UDP_MULTICAST_CLIENT_H
#define UDP_MULTICAST_CLIENT_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>

class UdpMulticastClient {
    public:
        UdpMulticastClient(const std::string& host, int port, const std::string& interface);
        ~UdpMulticastClient();

        bool joinGroup();
        bool receive(std::vector<uint8_t>& data, int expectedBytes);

    private:
        struct sockaddr_in _local_addr;
        std::string _host;  // Dirección IP multicast
        int _port;
        std::string _interface;  // Interfaz de red
        int _socketFd;
        char _buffer[1024];

};



#endif // UDP_MULTICAST_CLIENT_H