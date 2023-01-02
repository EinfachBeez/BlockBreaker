#ifndef LED_MATRIX_H
#define LED_MATRIX_H
#include <mbed.h>

class LedMatrix {
private:
    bool state[8][8] = {0};
    PortOut columns{PortB, 0xFF};
    PortOut rows{PortB, 0xFF00};
    Thread thread;


    void runUpdateThread();

public:
    LedMatrix(bool runAsync = true);
    bool* operator[] (size_t row);
    void updateMatrix();
};

#endif // LED_MATRIX_H