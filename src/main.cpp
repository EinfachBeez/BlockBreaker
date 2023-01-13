#include "../include/LedMatrix.h"
#include "../include/Joystick.h"
#include "../include/BlockBreaker.h"

Buzzer buzzer(PC_6);
LedMatrix ledMatrix;
Joystick joystick(PC_0, PC_1, PC_2);
BlockBreaker game(ledMatrix, joystick, buzzer);

int main() {
    ledMatrix.displayImage(MI_SMILEY_HAPPY);

    game.runGameLoop();
}

