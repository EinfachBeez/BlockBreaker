#include "../include/Buzzer.h"
#include <cstdint>

Buzzer::Buzzer(PinName buzzerPin) : pwmBuzzer(buzzerPin) {
}

void Buzzer::play(float frequency, std::chrono::duration<long long> time) {
    pwmBuzzer.period(frequency);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), time);
}

void Buzzer::playCollision() {
    pwmBuzzer.period(1.0/1000);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), 1s);
}

void Buzzer::resume() {
    pwmBuzzer.resume();
}

void Buzzer::stop() {
    pwmBuzzer.write(0);
}