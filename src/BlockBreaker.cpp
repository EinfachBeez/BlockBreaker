#include "../include/BlockBreaker.h"
#include <chrono>
#include <cstdint>

using namespace std::chrono;

BlockBreaker::BlockBreaker(LedMatrix& matrix, Joystick& joystick, Buzzer& buzzer): matrix(matrix), joystick(joystick), buzzer(buzzer) {
}

/**
*  Generates the 8x3 block which must be destroyed by the player
*/
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

    // handle border bounce
    if(ballXPos == 0) {
        ballXDirec = 1;
    }
        
    else if(ballXPos == 7) {
        ballXDirec = -1;
    }
        
    // top bounce
    if(ballYPos == 0) {
        ballYDirec = 1;
        return;
    }

    if(newYPos == 7) { // ball is going to enter bottom area
        uint8_t barStart = (uint8_t) barPos;
        uint8_t barEnd = uint8_t(barPos) + BAR_WIDTH - 1;

        if(newXPos == barStart && ballXDirec == 1 || newXPos == barEnd  && ballXDirec == -1) { // ball is going to hit player bar edge
            ballYDirec = -1;
            ballXDirec = -ballXDirec;
            buzzer.playCollision();
            return;
        }
        if(newXPos >= barStart - 1 && newXPos <= barEnd + 1) { // ball is going to hit player bar center
            ballYDirec = -1;
            buzzer.playCollision();
            return;
        }
        alive = false;
    }
}

bool BlockBreaker::hasWon() {
    for(uint8_t y = 0; y < BLOCK_AREA_Y; y++) {                 // iterate over rows in block area
        for(uint8_t x = 0; x < BLOCK_AREA_X; x++) {             // iterate over columns in current row
            if(matrix[y][x]) {                                  // check if current cell has been cleared
                if(ballXPos == x && ballYPos == y) continue;    // if cell has not been cleard it may be the ball
                return false;                                   // if it's not the ball return false
            }
        }
    }
    return true;                                                // return true if no uncleared point was found
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
    won = hasWon();
    if(!alive || won) return;

    // Write new position
    matrix[ballYPos][ballXPos] = 1;
}

void BlockBreaker::moveBar() {
    // Clear old position
    for (int i = 0; i < BAR_WIDTH; i++) {
        matrix[MATRIX_HEIGHT - 1][int(barPos) + i] = 0;
    }

    barPos += joystick.getXValue() * 0.5;

    if (barPos >= MAX_BAR_POS) 
        barPos = MAX_BAR_POS;
    else if (barPos < 0) 
        barPos = 0;
    
    for (int i = 0; i < BAR_WIDTH; i++) {
        matrix[MATRIX_HEIGHT - 1][int(barPos) + i] = 1;
    }
}


void BlockBreaker::gameInit() {
    gameActive = true;
    won = false;
    alive = true;
    ballXDirec = -1;
    ballYDirec = -1;
    ballXPos = 3;
    ballYPos = 6;
    matrix.clear();
    generateBlocks();
}

    

void BlockBreaker::runGameLoop() {
    while (true) {
        while(!joystick.getButtonValue()) ThisThread::sleep_for(10ms);

        gameInit();

        uint32_t tick = 0;
        uint32_t currentTick;
        timer.start();

        while(gameActive) {
            moveBar();
            ThisThread::sleep_for(50ms);

            currentTick = duration_cast<milliseconds>(timer.elapsed_time()).count();
            if(currentTick - tick > 300) {
                tick = currentTick;
                moveBall();
                gameActive = alive && !won;
            }
        }
        if(won) {
            matrix.displayImage(MI_SMILEY_HAPPY);
            buzzer.play(1.0/1500, 1s);
            buzzer.play(1.0/2000, 1s);
        } else {
            matrix.displayImage(MI_SMILEY_SAD);
            buzzer.play(1.0/500, 1s);
            buzzer.play(1.0/200, 1s);
        }
            

    }
}