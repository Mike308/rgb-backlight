#ifndef ANIMATION_H
#define ANIMATION_H
#include <Arduino.h>
class Animation {
    private: 
        unsigned long speed;
        uint8_t step;
        uint8_t mode;
        uint16_t color;
    public:
        Animation(uint8_t mode, unsigned long speed, uint8_t step);
        enum animationMode {NO_ANIMATION = 0, HSV_ROTATION = 1, RANDOM_COLOR = 2, SINGLE_COLOR = 4, BREATHING = 5};
        void setSpeed(unsigned long speed);
        void setStep(uint8_t step);
        void setMode(uint8_t mode);
        void setColor(uint16_t color);
        unsigned long getSpeed();
        uint8_t getStep();      
        uint8_t getMode();
        uint16_t getColor();
        String toString();
};
#endif