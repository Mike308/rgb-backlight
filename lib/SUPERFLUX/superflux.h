#ifndef SUPERFLUX_H 
#define SUPERFLUX_H
#include <Arduino.h>
#include "animation.h"
class Superflux {
    public:
        Superflux(uint8_t rPin, uint8_t gPin, uint8_t bPin);
        void animation(Animation * animation);
        void setRGB(uint8_t red, uint8_t green, uint8_t blue);
    private:
        uint8_t rPin;
        uint8_t gPin;
        uint8_t bPin;
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        void setHSV(uint16_t h, uint16_t s, uint16_t v, uint8_t *r, uint8_t *g, uint8_t *b);
        void hsvRotation(unsigned long currentTime, Animation *animation);
        void randomColor(unsigned long currentTime, Animation *animation);

};
#endif