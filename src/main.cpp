#include <mbed.h>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <ctime>

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"

#define sleep ThisThread::sleep_for


#define BLOCK_AREA_X 8
#define BLOCK_AREA_Y 3

LedMatrix ledMatrix;
Joystick joystick(PC_0, PC_1, PC_2);

// x > 0 rechts, x < 0 links, y > 0 unten, y < 0 oben
int ballXDirec = 1, ballYDirec = 1;

int ballXPosition = 3, ballYPosition = 6;


const std::vector<Pixel> startImage = {
    {1, 1}, {2, 1}, {1, 2}, {2, 2}, {5, 1}, {6, 1}, {5, 2}, {6, 2}, {0, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {7, 4}
};


void generateBlocks() {
    ledMatrix.clear();

    for (int i = 0; i < BLOCK_AREA_Y; i++) {
        for (int j = 0; j < BLOCK_AREA_X; j++) {
            ledMatrix[i][j] = 1;
        }
    }
}

/**
*   calculates collisions including changing direction of the ball and removing blocks
*   that have been broken
*/
void handleCollisions() {
    int newXPos = ballXPosition + ballXDirec;
    int newYPos = ballYPosition + ballYDirec;

    if(newYPos < BLOCK_AREA_Y && newXPos < BLOCK_AREA_X) { // new ball location is inside block area

        if(ledMatrix[newYPos][ballXPosition]) { // ball is going to collide with block above
            ledMatrix[newYPos][ballXPosition] = 0;
            ballYDirec = -ballYDirec;

        } else if(ledMatrix[ballYPosition][newXPos]) { // ball is going to collide with block beside
            ledMatrix[ballYPosition][newXPos] = 0;
            ballXDirec = -ballXDirec;

        } else if(ledMatrix[newYPos][newXPos]) { // ball is going to collide with block in front
            ledMatrix[newYPos][newXPos] = 0;
            ballXDirec = -ballXDirec;
            ballYDirec = -ballYDirec;
        }
    }


    if(ballXPosition == 0)
        ballXDirec = 1;
    else if(ballXPosition == 7)
        ballXDirec = -1;


    if(ballYPosition == 0)
        ballYDirec = 1;
    else if(ballYPosition == 7)
        ballYDirec = -1;
}

void moveBall() {
    // Clear old position
    ledMatrix[ballYPosition][ballXPosition] = 0;

    // transform ball posionsion by adding its 'velocity'
    ballXPosition += ballXDirec;
    ballYPosition += ballYDirec;

    
    assert(ballXPosition < 8);
    assert(ballXPosition >= 0);
    assert(ballYPosition < 8);
    assert(ballYPosition >= 0);
    

    handleCollisions();

    // Write new position
    ledMatrix[ballYPosition][ballXPosition] = 1;
}



int main() {

    bool gameState;

    ledMatrix.displayImage(startImage);

    sleep(2s);

    while (true) {

        generateBlocks();

        unsigned long millis;
        do {
            gameState = true;
            sleep(300ms);
            moveBall();
        } while (gameState);
    }
}

