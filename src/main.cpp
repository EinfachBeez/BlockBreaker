#include "../include/LedMatrix.h"
#include "../include/Joystick.h"
#include "../include/BlockBreaker.h"

LedMatrix ledMatrix;
Joystick joystick(PC_0, PC_1, PC_2);
BlockBreaker game(ledMatrix, joystick);

const std::vector<Pixel> startImage = {
    {1, 1}, {2, 1}, {1, 2}, {2, 2}, {5, 1}, {6, 1}, {5, 2}, {6, 2}, {0, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {7, 4}
};


int main() {
    ledMatrix.displayImage(startImage);

    ThisThread::sleep_for(2s);

    game.runGameLoop();
}

