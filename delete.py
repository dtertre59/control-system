# import socket

# MCAST_GRP = '224.0.0.1'  # Dirección multicast
# MCAST_PORT = 5007        # Puerto al que se enviará el mensaje

# # Crear el socket UDP
# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

# # Enviar un mensaje al grupo multicast
# message = "Hola desde el cliente multicast"
# sock.sendto(message.encode(), (MCAST_GRP, MCAST_PORT))

# print(f"Mensaje enviado a {MCAST_GRP}:{MCAST_PORT}")
# sock.close()

import socket
import struct

MCAST_GRP = '224.0.0.1'
MCAST_PORT = 5007

# Crear el socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

# Asociar el socket al puerto
sock.bind(('', MCAST_PORT))

# Unirse al grupo multicast
mreq = struct.pack('4s4s', socket.inet_aton(MCAST_GRP), socket.inet_aton('127.0.0.1'))  # Se usa '0.0.0.0' para que el sistema use la interfaz predeterminada
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

print(f"Escuchando mensajes en el grupo multicast {MCAST_GRP} y puerto {MCAST_PORT}...")

while True:
    # Recibir el mensaje del grupo multicast
    data, addr = sock.recvfrom(1024)
    print(f"Mensaje recibido: {data} desde {addr}")