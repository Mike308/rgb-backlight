#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "USART.h"
#include "superflux.h"
#include "animation.h"

void rxParse(String str);

Usart usart;
Animation *animation = new Animation(Animation::HSV_ROTATION, 25, 1);
Superflux superflux(5, 6, 3);
String rxString;
OneWire oneWire(9);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  // put your setup code here, to run once:
  usart.setOnReceiveCallback(&rxParse);
  Serial.begin(9600);
  temperatureSensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  superflux.animation(animation);
  usart.usartEvent(rxString);
}

void rxParse(String str) {
  char buf[256];
  str.toCharArray(buf, str.length());
  char *atCommand = strtok(buf, "=,?");
  if (!strcmp("AT+ANIM", atCommand)) {
    char *modeStr = strtok(NULL, ",");
    char *speedStr = strtok(NULL, ",");
    char *stepStr = strtok(NULL, ",");
    uint16_t speed = atoi(speedStr);
    uint8_t step = atoi(stepStr);
    uint8_t mode = atoi(modeStr);
    if (mode == Animation::HSV_ROTATION) {
      animation->setMode(Animation::HSV_ROTATION);
      animation->setSpeed(speed);
      animation->setStep(step);
    } else if (mode == Animation::RANDOM_COLOR) {
      animation->setMode(Animation::RANDOM_COLOR);
      animation->setSpeed(speed);
      animation->setStep(step);
    } else if (mode == Animation::NO_ANIMATION) {
      animation->setMode(Animation::NO_ANIMATION);
    } else if (mode == Animation::BREATHING) {
      animation->setMode(Animation::BREATHING);
      animation->setSpeed(speed);
      animation->setStep(step);
      char *hue = strtok(NULL, ",");
      char *saturation = strtok(NULL, ",");
      char *value = strtok(NULL, ",");
      animation->setColor(atoi(hue), atoi(saturation), atoi(value));
    }
  } else if (!strcmp("AT+RGB", atCommand)) {
    char *r = strtok(NULL, ",");
    char *g = strtok(NULL, ",");
    char *b = strtok(NULL, ",");
    superflux.setRGB(atoi(r), atoi(g), atoi(b));
    animation->setMode(Animation::NO_ANIMATION);
  } else if (!strcmp("AT+HSV", atCommand)) {
    char *h = strtok(NULL, ",");
    char *s = strtok(NULL, ",");
    char *v = strtok(NULL, ",");
    animation->setMode(Animation::NO_ANIMATION);
    superflux.setHSV(atoi(h), atoi(s), atoi(v));
  } else if (!strcmp("AT+TEMP", atCommand)) {
    temperatureSensor.requestTemperatures();
    Serial.println(temperatureSensor.getTempCByIndex(0));
  }
  rxString = "";
}

void serialEvent() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    rxString += c;
    if (c == '\n') {
      usart.setRxFlag(true);
    }
  }
}