#include "../include/BlockBreaker.h"

BlockBreaker::BlockBreaker(LedMatrix& matrix, Joystick& joystick): matrix(matrix), joystick(joystick) {
}


void BlockBreaker::generateBlocks() {
    matrix.clear();

    for (int i = 0; i < BLOCK_AREA_Y; i++) {
        for (int j = 0; j < BLOCK_AREA_X; j++) {
            matrix[i][j] = 1;
        }
    }
}


void BlockBreaker::handleCollisions() {
    int newXPos = ballXPos + ballXDirec;
    int newYPos = ballYPos + ballYDirec;

    if(newYPos < BLOCK_AREA_Y && newXPos < BLOCK_AREA_X) { // new ball location is inside block area

        if(matrix[newYPos][ballXPos]) { // ball is going to collide with block above
            matrix[newYPos][ballXPos] = 0;
            ballYDirec = -ballYDirec;

        } else if(matrix[ballYPos][newXPos]) { // ball is going to collide with block beside
            matrix[ballYPos][newXPos] = 0;
            ballXDirec = -ballXDirec;

        } else if(matrix[newYPos][newXPos]) { // ball is going to collide with block in front
            matrix[newYPos][newXPos] = 0;
            ballXDirec = -ballXDirec;
            ballYDirec = -ballYDirec;
        }
    }


    if(ballXPos == 0)
        ballXDirec = 1;
    else if(ballXPos == 7)
        ballXDirec = -1;


    if(ballYPos == 0)
        ballYDirec = 1;
    else if(ballYPos == 7)
        ballYDirec = -1;
}

void BlockBreaker::moveBall() {
    // Clear old position
    matrix[ballYPos][ballXPos] = 0;

    // transform ball posionsion by adding its 'velocity'
    ballXPos += ballXDirec;
    ballYPos += ballYDirec;

    // if the ball position is outside this bounds something went horribly wrong
    assert(ballXPos < 8);
    assert(ballXPos >= 0);
    assert(ballYPos < 8);
    assert(ballYPos >= 0);
    

    handleCollisions();


    // Write new position
    matrix[ballYPos][ballXPos] = 1;
}


void BlockBreaker::runGameLoop() {
    while (true) {

        generateBlocks();

        while(true) {
            ThisThread::sleep_for(300ms);
            moveBall();
        };
    }
}