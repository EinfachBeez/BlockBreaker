#include "../include/LedMatrix.h"

LedMatrix::LedMatrix(bool runAsync) {
    if(runAsync)
            this->thread.start(callback(this, &LedMatrix::runUpdateThread));
}

void LedMatrix::runUpdateThread() {
    while(true) {
            this->updateMatrix();
    }
}

bool* LedMatrix::operator[](size_t row) {
    return this->state[row];
}

void LedMatrix::updateMatrix() {
    for(uint8_t row = 0; row < 8; row++) {
        uint8_t rowData = 0;
        for(uint8_t column = 0; column < 8; column++) {
            rowData |= (this->state[row][column] << (7 - column));
        }
        this->rows.write(0);
        this->columns.write(~rowData);
        this->rows.write(1 << (8 + row));
    }
}