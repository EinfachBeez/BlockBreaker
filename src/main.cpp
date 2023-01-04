#include "mbed.h"
#include <chrono>
#include <cstdint>
#include <cstdio>

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"

#define sleep ThisThread::sleep_for

LedMatrix ledMatrix(false);
Joystick joystick(PC_0, PC_1, PC_2);
Timer gameTimer;

// x > 0 rechts, x < 0 links, y > 0 unten, y < 0 oben
int ballXDirec = 1, ballYDirec = 1;

int ballXPosition = 3, ballYPosition = 6;


uint8_t startScreenMatrix[][2] = {
    {1, 1}, {1, 2}, {2, 1}, {2, 2}, {1, 5}, {1, 6}, {2, 5}, {2, 6}, {4, 0}, {5, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {5, 6}, {4, 7}
};

void startScreen() {
    for (int i = 0; i < sizeof(startScreenMatrix)/sizeof(startScreenMatrix[0]); i++) {
        uint8_t x = startScreenMatrix[i][0];
        uint8_t y = startScreenMatrix[i][1];
        ledMatrix[x][y] = 1;
    }
}

void clearMatrix() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ledMatrix[i][j] = 0;
        }
    }
}

void generateBlocks() {
    clearMatrix();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            ledMatrix[i][j] = 1;
        }
    }
}

void moveBall() {
    // Clear old position
    //ledMatrix[ballYPosition][ballXPosition] = 0;

    printf("X: %i :: Y: %i\n", ballXPosition, ballYPosition);

    if (ballXPosition == 0 || ballXPosition == 7) ballXDirec = -ballXDirec;
    if (ballYPosition == 0 || ballYPosition == 7) ballYDirec = -ballYDirec;

    // Write new position
    ledMatrix[ballYPosition][ballXPosition] = 1;
}



int main() {

    bool gameState;

    startScreen();

    sleep(2s);

    while (true) {

        generateBlocks();

        unsigned long millis;
        gameTimer.start();
        do {
            gameState = true;

            unsigned long currentMillis = chrono::duration_cast<chrono::milliseconds>(gameTimer.elapsed_time()).count();
            if (!(currentMillis - millis > 300)) {
                ledMatrix.updateMatrix();
                continue;
            }
            millis = currentMillis;
            moveBall();

            ledMatrix.updateMatrix();
        } while (gameState);
    }
}

