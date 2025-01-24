#include <iostream>
#include"tcp_client.h"

int main() {
    string host = "127.0.0.1";
    TcpClient client(host, 12345);
    client.connect();
    std::string message = "Hello, Server!";
    std::vector<uint8_t> message_data(message.begin(), message.end());
    client.send(message_data);
    vector<uint8_t> data;
    client.receive(data, 15); // falla si recibe menos de 15 bytes
    // client.close();
    return 0;
}