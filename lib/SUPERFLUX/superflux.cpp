#include "superflux.h"
#include "animation.h"

Superflux::Superflux(uint8_t r, uint8_t g, uint8_t b) {
  this->rPin = r;
  this->gPin = g;
  this->bPin = b;
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void Superflux::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(rPin, red);
  analogWrite(gPin, green);
  analogWrite(bPin, blue);
}

void Superflux::setHSV(uint16_t hue, uint16_t saturation, uint16_t value){
  RGB colorRGB = hsvToRGB(hue, saturation, value);
  setRGB(colorRGB.getRed(), colorRGB.getGreen(), colorRGB.getBlue());
}

void Superflux::animation(Animation * animation) {
  unsigned long currentTime = millis();
  if (animation->getMode() == Animation::HSV_ROTATION) {
    hsvRotation(currentTime, animation);
  } else if (animation->getMode() == Animation::RANDOM_COLOR) {
    randomColor(currentTime, animation);
  }else if (animation->getMode() == Animation::BREATHING){
    breathingColor(currentTime, animation);
  }  else if (animation->getMode() == Animation::NO_ANIMATION) {

  }
}

RGB Superflux::hsvToRGB(uint16_t h, uint8_t s, uint8_t v){
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
  return RGB(red, green, blue);
}

void Superflux::hsvRotation(unsigned long currentTime, Animation *animation) {
  static unsigned long previousTime = 0;
  static uint16_t h = 0;
  if (currentTime - previousTime >= animation->getSpeed()) {
    previousTime = currentTime;
    RGB rgbColor = hsvToRGB(h, 100, 100);
    setRGB(rgbColor.getRed(), rgbColor.getGreen(), rgbColor.getBlue());
    if (h > 360)
      h = 0;
    h+=animation->getStep();
  }
}

void Superflux::randomColor(unsigned long currentTime, Animation *animation) {
  static unsigned long previousTime = 0;
  if (currentTime - previousTime >= animation->getSpeed()) {
    previousTime = currentTime;
    uint8_t r = random(256);
    uint8_t g = random(256);
    uint8_t b = random(256);
    setRGB(r, g, b);
  }
}

void Superflux::breathingColor(unsigned long currentTime, Animation *animation){
  static unsigned long previousTime = 0;
  static int value = 0;
  static uint8_t state = 0;
  if (currentTime - previousTime >= animation->getSpeed()){
     previousTime = currentTime;
    if (state == 0){
      RGB rgbColor = hsvToRGB(animation->getColor().getHue(), animation->getColor().getSaturation(), value);
      setRGB(rgbColor.getRed(), rgbColor.getGreen(), rgbColor.getBlue());
      value+=animation->getStep();  
      if (value == animation->getColor().getValue()) state = 1;
    } else {
        RGB rgbColor = hsvToRGB(animation->getColor().getHue(), animation->getColor().getSaturation(), value);
        setRGB(rgbColor.getRed(), rgbColor.getGreen(), rgbColor.getBlue());
        value-=animation->getStep();
        if (value == 0) state = 0;
    }
  }
}


