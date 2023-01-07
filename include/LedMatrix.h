#ifndef LED_MATRIX_H
#define LED_MATRIX_H
#include <mbed.h>
#include <vector>

#define MATRIX_HEIGHT 8
#define MATRIX_WIDTH 8

struct Pixel {
    uint8_t x;
    uint8_t y;
};

class LedMatrix {
private:
    bool state[8][8] = {0};
    PortOut columns{PortB, 0xFF};
    PortOut rows{PortB, 0xFF00};
    Thread thread;


    void runUpdateThread();

public:
    /**
    * Create an object to run the matrix
    * @param runAsync specifies if the matrix should be updated in a seperate thread
    * if this is false you have to repeatedly call `updateMatrix()`
    */
    LedMatrix(bool runAsync = true);

    /**
    * used to update the display data
    *
    * @returns a pointer to an array of the specified row
    */
    bool* operator[] (size_t row);

    /**
    * displays an image of pixel values
    * @param pixels the collection of pixel values to enable
    */
    void displayImage(const std::vector<Pixel>& pixels);

    /**
    * Call this method in repeat to update the outputs to the matrix.
    * @note Only call this if runAsync was set to false
    */
    void updateMatrix();

    /**
    * Disables all led's in the matrix.
    */
    void clear();
};

#endif // LED_MATRIX_H