#include <iostream>
#include"actuator.h"

int main() {

    Actuator actuator(1);

    actuator.init();
    actuator.move();
    actuator.close();
   
    return 0;
}