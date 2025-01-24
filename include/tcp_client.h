#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <cstring>    // Para usar memset
#include <unistd.h>   // Para la función close
#include <sys/socket.h> // Para el socket y las funciones relacionadas
#include <netinet/in.h> // Para las funciones relacionadas con las direcciones
#include <arpa/inet.h>  // Para inet_pton

using namespace std;

/*
* TCP Client class
*/
class TcpClient {

    public:
        TcpClient(string& host, int port);
        ~TcpClient();

        bool connect();
        void close();

        bool send(const std::vector<uint8_t>& data);
        bool receive(std::vector<uint8_t>& data, int expectedBytes);

    private:
        struct sockaddr_in _serverAddr;
        string _host;  // ip
        int _port;
        int _socketFd;
        char _buffer[1024];

};

#endif // TCP_CLIENT_H
