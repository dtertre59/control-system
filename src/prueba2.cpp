#include"prueba2.h"
#include<iostream>


Prueba2::Prueba2() {
    // Constructor implementation here
    someMember = 3;
    std::cout << "Constructor de Prueba2..." << std::endl;
    return;
}

Prueba2::~Prueba2() {
    // Destructor implementation here
    std::cout << "Destructor de Prueba2..." << std::endl;
    return;
}

void Prueba2::someMethod() {
    // Method implementation here
    std::cout << "Doing something in Prueba2... value" << someMember << std::endl;
    return;
}

