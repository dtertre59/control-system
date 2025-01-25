#include<iostream>


class Actuator {
    public:
        Actuator(int serialPort);
        ~Actuator();

        void init();
        void move();
        void close();

    private:
        int _serialPort;
        bool _isInitialized;
};