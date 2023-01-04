#include "mbed.h"
#include <cstdint>
#include <cstdio>

#include "../include/LedMatrix.h"
#include "../include/Joystick.h"
#include "../include/LCDDisplay.h"

#define sleep ThisThread::sleep_for

LedMatrix ledMatrix;
Joystick joystick(PC_0, PC_1, PC_2);
LCDDisplay lcdDisplay;

Thread titleThread;

uint8_t startScreenMatrix[][2] = {
    {1, 1}, {1, 2}, {2, 1}, {2, 2}, {1, 5}, {1, 6}, {2, 5}, {2, 6}, {4, 0}, {5, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {5, 6}, {4, 7}
};

void printTitle() {
    bool x;
    lcdDisplay.cursorpos(2);
    while (true) {
        if (x) {
            lcdDisplay.clear();
            lcdDisplay.cursorpos(2);
            x = !x;
            sleep(500ms);
            continue;
        }
        x = !x;
        lcdDisplay.printf("Blockbreaker");
        lcdDisplay.cursorpos(64 + 4);
        lcdDisplay.printf("-Start-");
        sleep(500ms);
    }
    
}

void startScreen() {
    lcdDisplay.clear();

    for (int i = 0; i < sizeof(startScreenMatrix)/sizeof(startScreenMatrix[0]); i++) {
        uint8_t x = startScreenMatrix[i][0];
        uint8_t y = startScreenMatrix[i][1];
        ledMatrix[x][y] = 1;
    }

    titleThread.start(printTitle);
}

int main() {

    startScreen();   

    while (true) {
        ledMatrix.updateMatrix();
    }

    ThisThread::sleep_for(10h);
}

