#include "udp_multicast_client.h"

#include <iostream>
#include <cstring>    // Para usar memset
#include <unistd.h>   // Para la función close
#include <sys/socket.h> // Para el socket y las funciones relacionadas
#include <netinet/in.h> // Para las funciones relacionadas con las direcciones
#include <arpa/inet.h>  // Para inet_pton

UdpMulticastClient::UdpMulticastClient(const std::string& host, int port, const std::string& interface) {
    _host = host;
    _port = port;
    _interface = interface;
    
    // Crear el socket UDP
    _socketFd= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_socketFd < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Hacer bind al puerto
    memset(&_local_addr, 0, sizeof(_local_addr));
    _local_addr.sin_family = AF_INET;
    _local_addr.sin_port = htons(_port);
    _local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(_socketFd, (struct sockaddr*)&_local_addr, sizeof(_local_addr)) < 0) {
        perror("Error al hacer bind");
        close(_socketFd);
        exit(1);
    }
}

UdpMulticastClient::~UdpMulticastClient() {
    close(_socketFd);
}

bool UdpMulticastClient::joinGroup() {
    // Unirse al grupo multicast
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(_host.c_str());  // Dirección multicast
    mreq.imr_interface.s_addr = inet_addr(_interface.c_str()); // Interfaz loopback (localhost)
    
    if (setsockopt(_socketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("Error al unirse al grupo multicast");
        close(_socketFd);
        exit(1);
    }

    std::cout << "Escuchando mensajes en el grupo multicast " << _host 
              << " y puerto " << _port << "..." << std::endl;
    return true;
}

bool UdpMulticastClient::receive(std::vector<uint8_t>& data, int expectedBytes) {
    // Recibir el mensaje del grupo multicast
    // char buffer[1024];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    ssize_t recv_len = recvfrom(_socketFd, data.data(), data.size(), 0, (struct sockaddr*)&addr, &addr_len);
    if (recv_len < 0) {
        perror("Error al recibir el mensaje");
        return false;
    }
    
    data[recv_len] = '\0';  // Asegurar que el mensaje esté terminado en nulo
    std::cout << "Mensaje recibido: " << std::string(data.begin(), data.end()) << " desde " 
              << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
    
    return true;
}
