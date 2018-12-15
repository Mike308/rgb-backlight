#ifndef ANIMATION_H
#define ANIMATION_H
#include <Arduino.h>
#include "hsv.h"
class Animation {
    public:
        Animation(uint8_t mode, unsigned long speed, uint8_t step);
        enum animationMode {NO_ANIMATION = 0, HSV_ROTATION = 1, RANDOM_COLOR = 2, SINGLE_COLOR = 4, BREATHING = 5};
        void setSpeed(unsigned long speed);
        void setStep(uint8_t step);
        void setMode(uint8_t mode);
        unsigned long getSpeed();
        uint8_t getStep();      
        uint8_t getMode();
        String toString();
        HSV getColor();
        void setColor(uint16_t hue, uint8_t saturation, uint8_t value);
    private: 
        unsigned long speed;
        uint8_t step;
        uint8_t mode;
        HSV color;
};
#endif