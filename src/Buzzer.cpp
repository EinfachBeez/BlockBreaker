#include "../include/Buzzer.h"
#include <chrono>
#include <cstdint>
#include <ratio>

Buzzer::Buzzer(PinName buzzerPin) : pwmBuzzer(buzzerPin) {
}

void Buzzer::play(float frequency, std::chrono::duration<long long> time) {
    pwmBuzzer.period(frequency);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), time);
}

void Buzzer::playCollision() {
    pwmBuzzer.period(1.0/460);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), 200ms);
}

void Buzzer::resume() {
    pwmBuzzer.resume();
}

void Buzzer::stop() {
    pwmBuzzer.write(0);
}