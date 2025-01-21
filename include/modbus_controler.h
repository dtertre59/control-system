#ifndef MODBUS_CONTROLLER_H
#define MODBUS_CONTROLLER_H

#include <cstdint>
#include <vector>

class ModbusController {
 private:
    int m_serialPort;
    bool m_isInitialized;

public:
    ModbusController();
    ~ModbusController();

    // Helper functions
    bool openPort(const char* portName, int baudRate);
    
    void closePort();

    // Initialize the Modbus communication
    bool init(const char* portName, int baudRate);

    // Close the Modbus communication
    void close();

    // Send data via Modbus
    bool send(const std::vector<uint8_t>& data);

    // Receive data via Modbus
    bool receive(std::vector<uint8_t>& data, int expectedBytes);

};

#endif // MODBUS_CONTROLLER_H