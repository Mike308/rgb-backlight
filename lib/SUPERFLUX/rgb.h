#ifndef RGB_H
#define RGB_H
#include <Arduino.h>
class RGB{

    public:
        RGB(uint8_t red, uint8_t green, uint8_t blue);
        uint8_t getRed();
        uint8_t getGreen();
        uint8_t getBlue();
    private:
        uint8_t red;
        uint8_t green;
        uint8_t blue;
};
#endif