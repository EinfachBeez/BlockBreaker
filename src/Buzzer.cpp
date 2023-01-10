#include "../include/Buzzer.h"
#include <cstdint>

Buzzer::Buzzer(PinName buzzerPin) : pwmBuzzer(buzzerPin) {
}

void Buzzer::play(float frequency, uint16_t time) {
    pwmBuzzer.period(frequency);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), time);
}

void Buzzer::playCollision() {
    pwmBuzzer.period(1/1000);
    pwmBuzzer.write(0.5);
    timeout.attach(callback(this, &Buzzer::stop), 1);
}

void Buzzer::resume() {
    pwmBuzzer.resume();
}

void Buzzer::stop() {
    pwmBuzzer.write(0);
}