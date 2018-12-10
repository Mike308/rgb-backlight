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

unsigned long Animation::getSpeed(){
    return speed;
}

uint8_t Animation::getStep(){
    return step;
}

uint8_t Animation::getMode(){
    return mode;
}

String Animation::toString(){
    return "mode: " + String(mode) + " step" + String(step) + " speed: " + String(speed); 
}

