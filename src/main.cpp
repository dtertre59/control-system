#include <iostream>
#include"prueba.h"
#include"prueba2.h"

int main() {
    std::cout << "¡Hola, Mundo!" << std::endl;
    doSomething();

    Prueba2 a;
    a.someMethod();
    return 0;
}