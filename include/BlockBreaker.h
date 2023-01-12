#ifndef BLOCK_BREAKER_H
#define BLOCK_BREAKER_H

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"
#include "../include/Buzzer.h"
#include <cstdint>


#define BLOCK_AREA_X 8
#define BLOCK_AREA_Y 3

#define BAR_WIDTH 2
#define MAX_BAR_POS (8 - BAR_WIDTH)

class BlockBreaker {
private:
    LedMatrix& matrix;
    Joystick& joystick;
    Buzzer& buzzer;
    Timer timer;

    int8_t ballXDirec;
    int8_t ballYDirec;

    uint8_t ballXPos;
    uint8_t ballYPos;

    float barPos = MAX_BAR_POS / 2.0;
    
    bool alive = true;
    bool won = false;
    bool gameActive = false;

    void generateBlocks();
    /**
    *   calculates collisions including changing direction of the ball and removing blocks
    *   that have been broken
    */
    void handleCollisions();
    bool hasWon();
    void moveBall();
    void moveBar();
    void gameInit();

public:
    BlockBreaker(LedMatrix& matrix, Joystick& joystick, Buzzer& buzzer);
    void runGameLoop();
};

#endif // BLOCK_BREAKER_H