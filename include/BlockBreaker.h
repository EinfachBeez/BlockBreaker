#ifndef BLOCK_BREAKER_H
#define BLOCK_BREAKER_H

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"
#include <cstdint>


#define BLOCK_AREA_X 8
#define BLOCK_AREA_Y 3

#define BAR_WIDTH 2
#define MAX_BAR_POS (8 - BAR_WIDTH)


class BlockBreaker {
private:
    LedMatrix& matrix;
    Joystick& joystick;
    Timer timer;

    int8_t ballXDirec = 1;
    int8_t ballYDirec = 1;

    uint8_t ballXPos = 3;
    uint8_t ballYPos = 6;

    float barPos = MAX_BAR_POS / 2.0;

    void generateBlocks();
    /**
    *   calculates collisions including changing direction of the ball and removing blocks
    *   that have been broken
    */
    void handleCollisions();
    void moveBall();
    void moveBar();

public:
    BlockBreaker(LedMatrix& matrix, Joystick& joystick);
    void runGameLoop();
};

#endif // BLOCK_BREAKER_H