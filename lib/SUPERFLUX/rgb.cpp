#include "rgb.h"

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

uint8_t RGB::getRed(){
    return red;
}

uint8_t RGB::getGreen(){
    return green;
}

uint8_t RGB::getBlue(){
    return blue;
}

