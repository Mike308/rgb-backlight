#include "superflux.h"
#include "animation.h"

Superflux::Superflux(uint8_t r, uint8_t g, uint8_t b){
    this->rPin = r;
    this->gPin = g;
    this->bPin = b;
    pinMode(r,OUTPUT);
	pinMode(g,OUTPUT);
	pinMode(b,OUTPUT);
}

void Superflux::setRGB(uint8_t r, uint8_t b, uint8_t g){
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);
}

void Superflux::animation(Animation animation){
    unsigned long currentTime = millis();
    if (animation.getMode() == Animation::HSV_ROTATION){
        hsvRotation(currentTime, animation.getSpeed());
    }else if (animation.getMode() == Animation::RANDOM_COLOR){

    }else if (animation.getMode() == Animation::NO_ANIMATION){

    }
}

void Superflux::setHSV(uint16_t h, uint16_t s, uint16_t v, uint8_t *r, uint8_t *g, uint8_t *b){
  uint8_t diff;
  uint8_t red, green, blue;

  if (h > 359)
    h = 359;
  if (s > 100)
    s = 100;
  if (v > 100)
    v = 100;

  if (h < 61) {
    red = 255;
    green = (425 * h) / 100;
    blue = 0;
  } else if (h < 121) {
    red = 255 - ((425 * (h - 60)) / 100);
    green = 255;
    blue = 0;
  } else if (h < 181) {
    red = 0;
    green = 255;
    blue = (425 * (h - 120)) / 100;
  } else if (h < 241) {
    red = 0;
    green = 255 - ((425 * (h - 180)) / 100);
    blue = 255;
  } else if (h < 301) {
    red = (425 * (h - 240)) / 100;
    green = 0;
    blue = 255;
  } else {
    red = 255;
    green = 0;
    blue = 255 - ((425 * (h - 300)) / 100);
  }

  s = 100 - s;
  diff = ((255 - red) * s) / 100;
  red = red + diff;
  diff = ((255 - green) * s) / 100;
  green = green + diff;
  diff = ((255 - blue) * s) / 100;
  blue = blue + diff;

  red = (red * v) / 100;
  green = (green * v) / 100;
  blue = (blue * v) / 100;
  *r = red;
  *g = green;
  *b = blue;
}

void Superflux::hsvRotation(unsigned long currentTime, unsigned long speed){
    static unsigned long previousTime = 0;
    static uint16_t h = 0;
    if (currentTime - previousTime >= speed){
        previousTime = currentTime;
        setHSV(h, 100, 100, &r, &g, &b);
        setRGB(r, g, b);
        if (h > 360) h = 0;
        h++;

    }
}



