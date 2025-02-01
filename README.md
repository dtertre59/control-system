# Control System

## Dependencies

- gcc
- make
- cmake

## Create

- mkdir build
- cd build
- cmake ..
- make
- ./control_system

# Convencion en el formato de las variables en c

- Variables locales: camelCase
- Atributos de las clases (miembros privados): _camelCase
- Metodos de las clases: camelCase
- Constantes: UPPER_SNAKE_CASE
- Parametros de funciones: camelCase
- Clases: PascalCase
- Enumeracions: PascalCase y los valores en UPPER_SNAKE_CASE
- tipos de dato: PascalCase (por convención) o UPPER_CASE dependiendo del tipo.
- Variables globales: g_camelCase


# Libreria utizada para la interaccion cobn los pines gpio de la Raspberrry PI

- pigpio
- Viene instalada en el sistema.
- Para comprobar si esta instalada: dpkg -s pigpio
- Comando para instalar la libreria: sudo apt install pigpio
- Verificar si el servicio esta en funcionamiento (proceso demonio): sudo systemctl status pigpiod
- Si no estivo se puede activar con: sudo systemctl start pigpiod
- Si quieres que se active cuando se enciende el ordenador: sudo systemctl enable pigpiod

Para el primer programa es necesario que este deshabilitado.
