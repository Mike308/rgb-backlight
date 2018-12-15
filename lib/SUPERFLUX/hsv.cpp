#include "hsv.h"

HSV::HSV(){
    
}

HSV::HSV(uint16_t hue, uint8_t saturation, uint8_t value){
    this->hue = hue;
    this->saturation = saturation;
    this->value = value;
}

void HSV::setHue(uint16_t hue){
    this->hue = hue;
}

void HSV::setSaturation(uint8_t saturation){
    this->saturation = saturation;
}

void HSV::setValue(uint8_t value){
    this->value = value;
}

uint16_t HSV::getHue(){
    return hue;
}

uint8_t HSV::getSaturation(){
    return saturation;
}

uint8_t HSV::getValue(){
    return value;
}