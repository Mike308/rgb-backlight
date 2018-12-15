#include "animation.h"

Animation::Animation(uint8_t mode, unsigned long speed, uint8_t step){
    this->mode = mode;
    this->speed = speed;
    this->step = step;    
}

void Animation::setSpeed(unsigned long speed){
    this->speed = speed;
}

void Animation::setStep(uint8_t step){
    this->step = step;
}

void Animation::setMode(uint8_t mode){
    this->mode = mode;
}

void Animation::setColor(uint16_t hue, uint8_t saturation, uint8_t value){
    color.setHue(hue);
    color.setSaturation(saturation);
    color.setValue(value);
}

unsigned long Animation::getSpeed(){
    return speed;
}

uint8_t Animation::getStep(){
    return step;
}

uint8_t Animation::getMode(){
    return mode;
}

HSV Animation::getColor(){
    return color;
}

String Animation::toString(){
    return "mode: " + String(mode) + " step" + String(step) + " speed: " + String(speed);
}

