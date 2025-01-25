#include "actuator.h"

Actuator::Actuator(int serialPort) {
    _serialPort = serialPort;
    _isInitialized = false;
}

Actuator::~Actuator() {
    close();
}


void Actuator::init() {
    if (_isInitialized) {
        std::cout << "Actuator already initialized" << std::endl;
        return;
    }
    // Initialize actuator
    _isInitialized = true;
}

void Actuator::move() {
    if (!_isInitialized) {
        std::cout << "Actuator not initialized" << std::endl;
        return;
    }
    // Move actuator
    std::cout << "Actuator is moving" << std::endl;
}

void Actuator::close() {
    if (!_isInitialized) {
        std::cout << "Actuator not initialized" << std::endl;
        return;
    }
    // Close actuator
    _isInitialized = false;
    std::cout << "Actuator closed" << std::endl;
}