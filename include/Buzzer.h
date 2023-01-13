#ifndef BUZZER_H
#define BUZZER_H
#include <cstdint>
#include <mbed.h>

class Buzzer {
private:
    PwmOut pwmBuzzer;
    Timeout timeout;

public:
    Buzzer(PinName buzzerPin);

    void play(float frequency, std::chrono::duration<long long> time);
    void resume();
    void stop();
    void playCollision();

};

#endif //BUZZER_H