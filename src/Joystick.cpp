#include <chrono>
#include <Timer.h>
#include <cstdio>
#include "../include/Joystick.h"

using namespace std::chrono;

Joystick::Joystick(PinName xPin, PinName yPin, PinName buttonPin) : xAxis(xPin), yAxis(yPin), button(buttonPin) {
    this->button.mode(PullUp);
    this->button.rise(callback(this, &Joystick::buttonRise));
    this->button.fall(callback(this, &Joystick::buttonFall));
    this->button.enable_irq();
    this->buttonDebounce.start();
}

float Joystick::getXValue() {
    this->xValue = xAxis.read();

    this->xValue = xValue * 2 - 1;
    this->xValue = xValue > -0.1 && xValue < 0.1 ? 0 : xValue;

    return this->xValue;
}

float Joystick::getYValue() {
    this->yValue = yAxis.read();

    this->yValue = yValue * 2 - 1;
    this->yValue = yValue > -0.1 && yValue < 0.1 ? 0 : yValue;

    return this->yValue;
}

bool Joystick::getButtonValue() {
    return this->buttonValue;
}

void Joystick::buttonRise() {
    if (!(duration_cast<milliseconds>(buttonDebounce.elapsed_time()).count() > 10)) return;
    this->buttonValue = false;
    this->buttonDebounce.reset();
}

void Joystick::buttonFall() {
    if (!(duration_cast<milliseconds>(buttonDebounce.elapsed_time()).count() > 10)) return;
    this->buttonValue = true;
    
}

