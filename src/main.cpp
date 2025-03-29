#include <iostream>
#include <unistd.h>
#include <thread>
#include"tcp_client.h"
#include"udp_multicast_client.h"
#include "coordinator.h"

// // int main() {
// //     string host = "127.0.0.1";
// //     TcpClient client(host, 5001);
// //     client.connect();
// //     std::string message = "Hello, Server!";
// //     std::vector<uint8_t> message_data(message.begin(), message.end());

// //     for (int i = 0; i < 10; ++i) {
// //         client.send(message_data);
// //         vector<uint8_t> data;
// //         client.receive(data, 1024); // falla si recibe menos de 15 bytes
// //         sleep(1);  // Pausa durante 3 segundos

// //     }
    
// //     client.close();
// //     return 0;
// // }


// --------- COORDINATOR ----------- // 

int main() {

    Coordinator coordinator;

    coordinator.run();

    return 0;
}



// ----- THREAD ----------- //
// #include <iostream>
// #include <thread>
 
// using namespace std;
 
// void func(int n, double m){
//     cout << n << " " << m << endl;
// }
 
// int main(){
//     thread th(func, 1, 5.7);
    
//     if(th.joinable()) {
//         th.join();
//     }
// }



// ----- UDP MULTICAST CLIENT USING CLASS ----- # 

// typedef struct {
//     int material;
//     int timestamp;
// } Piece;

// int main() {
//     string host = "224.0.0.1";  // Dirección del grupo multicast
//     int port = 5007;  // Puerto multicast
//     string interface = "127.0.0.1";  // Interfaz de red (localhost)

//     UdpMulticastClient client(host, port, interface);

//     // Unirse al grupo multicast
//     if (!client.joinGroup()) {
//         cerr << "Error al unirse al grupo multicast" << endl;
//         return 1;
//     }

//     cout << "Unido al grupo multicast" << endl;

//     // Recibir datos
//     vector<uint8_t> data;
//     Piece p;

//     while (true) {
//         std::cout << "Esperando datos..." << std::endl;
//         data.clear();  // Limpiar el vector de datos
//         data.resize(1024);  // Reservar espacio para los datos
//         // Recibir el mensaje del grupo multicast
//         if (client.receive(data, 1024)) {
//             memcpy(&p, data.data(), sizeof(Piece));
//             // Procesar datos recibidos
//             cout << "Recibido: \nMaterial: " << p.material << "\nTimestamp: " << p.timestamp << endl;
//         }
//     }

//     return 0;
// }




// UDP MULTICAST CLIENT ---------------------------------

// #include <iostream>
// #include <cstring>
// #include <cstdlib>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>

// #define MCAST_GRP "224.0.0.1"
// #define MCAST_PORT 5007

// int main() {
//     // Crear el socket UDP
//     int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//     if (sock < 0) {
//         perror("Error al crear el socket");
//         exit(1);
//     }

//     // Hacer bind al puerto
//     struct sockaddr_in local_addr;
//     memset(&local_addr, 0, sizeof(local_addr));
//     local_addr.sin_family = AF_INET;
//     local_addr.sin_port = htons(MCAST_PORT);
//     local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

//     if (bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
//         perror("Error al hacer bind");
//         close(sock);
//         exit(1);
//     }

//     // Unirse al grupo multicast
//     struct ip_mreq mreq;
//     mreq.imr_multiaddr.s_addr = inet_addr(MCAST_GRP);  // Dirección multicast
//     mreq.imr_interface.s_addr = inet_addr("127.0.0.1"); // Interfaz loopback (localhost)
    
//     if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
//         perror("Error al unirse al grupo multicast");
//         close(sock);
//         exit(1);
//     }

//     std::cout << "Escuchando mensajes en el grupo multicast " << MCAST_GRP 
//               << " y puerto " << MCAST_PORT << "..." << std::endl;

//     while (true) {
//         // Recibir el mensaje del grupo multicast
//         char buffer[1024];
//         struct sockaddr_in addr;
//         socklen_t addr_len = sizeof(addr);

//         ssize_t recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
//         if (recv_len < 0) {
//             perror("Error al recibir el mensaje");
//             break;
//         }
        
//         buffer[recv_len] = '\0';  // Asegurar que el mensaje esté terminado en nulo
//         std::cout << "Mensaje recibido: " << buffer << " desde " 
//                   << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
//     }

//     close(sock);
//     return 0;
// }