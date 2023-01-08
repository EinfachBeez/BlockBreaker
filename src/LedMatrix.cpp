#include "../include/LedMatrix.h"

LedMatrix::LedMatrix(bool runAsync) {
    // start update thread if runAsync was set to true
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

void LedMatrix::displayImage(const std::vector<Pixel> &pixels) {
    this->clear();
    for(const Pixel& pixel : pixels) {
        this->state[pixel.y][pixel.x] = true;
    }
}

void LedMatrix::updateMatrix() {
    for(uint8_t row = 0; row < 8; row++) {                          // iterate over each row
        uint8_t rowData = 0;                                        
        for(uint8_t column = 0; column < 8; column++) {             // iterate over each pixel in current row
            rowData |= (this->state[row][column] << (7 - column));  // get current pixel and shift data to corresponding bit in byte
        }
        this->rows.write(0);                                        // disable all row outputs to prevent unwanted behavior
        this->columns.write(~rowData);                              // write inverted pixel data for row -> pull enabled pixels low
        this->rows.write(1 << (8 + row));                           // pull current row high, while keeping every othe low
    }
}

void LedMatrix::clear() {
    for(uint8_t y = 0; y < 8; y++) {
        for(uint8_t x = 0; x < 8; x++) {
            this->state[x][y] = false;
        }
    }
}