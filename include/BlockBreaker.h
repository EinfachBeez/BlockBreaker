#ifndef BLOCK_BREAKER_H
#define BLOCK_BREAKER_H

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"


#define BLOCK_AREA_X 8
#define BLOCK_AREA_Y 3


class BlockBreaker {
private:
    LedMatrix& matrix;
    Joystick& joystick;

    int8_t ballXDirec = 1;
    int8_t ballYDirec = 1;

    uint8_t ballXPos = 3;
    uint8_t ballYPos = 6;

    void generateBlocks();
    /**
    *   calculates collisions including changing direction of the ball and removing blocks
    *   that have been broken
    */
    void handleCollisions();
    void moveBall();

public:
    BlockBreaker(LedMatrix& matrix, Joystick& joystick);
    void runGameLoop();
};

#endif // BLOCK_BREAKER_H