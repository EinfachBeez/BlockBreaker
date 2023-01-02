#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <mbed.h>

class Joystick {
private:
    AnalogIn xAxis;
    AnalogIn yAxis;
    InterruptIn button;
    Timer buttonDebounce;

    float xValue;
    float yValue;
    bool buttonValue;

    void buttonRise();
    void buttonFall();

public:
    Joystick(PinName xPin, PinName yPin, PinName buttonPin);

    float getXValue();
    float getYValue();
    bool getButtonValue();
};

#endif //JOYSTICK_H