#include"tcp_client.h"
#include<iostream>

#include <iostream>
#include <cstring>    // Para usar memset
#include <unistd.h>   // Para la función close
#include <sys/socket.h> // Para el socket y las funciones relacionadas
#include <netinet/in.h> // Para las funciones relacionadas con las direcciones
#include <arpa/inet.h>  // Para inet_pton

using namespace std;


TcpClient::TcpClient(string& host, int port) {
    _host = host;
    _port = port;
    _socketFd = 0;
    _buffer[0] = 0;  // init buffer with 0
    // Set server address
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(port);
}

TcpClient::~TcpClient() {
    close();
}


bool TcpClient::connect() {
    // Create socket
    if ((_socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        return false;
    }
    
    // Configure server address / Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, _host.c_str(), &_serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return false;
    }

    // Connect to server
    if (::connect(_socketFd, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0) {
        cerr << "Connection Failed" << endl;
        return false;
    }
    return true;
}


void TcpClient::close() {
    if (_socketFd > 0) {
        ::close(_socketFd);
    }
}


bool TcpClient::send(const std::vector<uint8_t>& data) {
    if (::send(_socketFd, data.data(), data.size(), 0) < 0) {
        cerr << "Send failed" << endl;
        return false;
    }
    return true;
}


bool TcpClient::receive(std::vector<uint8_t>& data, int expectedBytes = 1024) {
    int bytesRead = ::recv(_socketFd, _buffer, expectedBytes, 0);
    if (bytesRead < 0) {
        cerr << "Receive failed" << endl;
        return false;
    }
    cout << "Received " << bytesRead << " bytes" << endl;


    data.assign(_buffer, _buffer + bytesRead);

    // Convert received data to string
    std::string receivedData(data.begin(), data.end());
    std::cout << "Received data: " << receivedData << std::endl;

    return true;
}
