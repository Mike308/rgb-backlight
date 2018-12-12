#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "USART.h"
#include "superflux.h"
#include "animation.h"

void rxParse(String str);

Usart usart;
Animation * animation = new Animation(Animation::HSV_ROTATION, 1000, 1);
Superflux superflux(5, 6, 3);
String rxString;
OneWire oneWire(9);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  // put your setup code here, to run once:
  usart.setOnReceiveCallback(&rxParse);
  Serial.begin(9600);
  Serial.println("Test");
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
  Serial.println(str);
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
      Serial.println(animation->toString());
    }else if (mode == Animation::RANDOM_COLOR){
      animation->setMode(Animation::RANDOM_COLOR);
      animation->setSpeed(speed);
      animation->setStep(step);
      Serial.println(animation->toString());
    }else if (mode == Animation::NO_ANIMATION){
      animation->setMode(Animation::NO_ANIMATION);
      Serial.println(animation->toString());
    }else if (mode == Animation::BREATHING){
      animation->setMode(Animation::BREATHING);
      animation->setSpeed(speed);
      animation->setStep(step);
      char *colorStr = strtok(NULL, ",");
      uint16_t color = atoi(colorStr);
      animation->setColor(color);
    }
  } else if (!strcmp("AT+RGB", atCommand)) {
    char *r = strtok(NULL, ",");
    char *g = strtok(NULL, ",");
    char *b = strtok(NULL, ",");
    uint8_t rVal = atoi(r);
    uint8_t gVal = atoi(g);
    uint8_t bVal = atoi(b);
    superflux.setRGB(rVal, gVal, bVal);
    animation->setMode(Animation::NO_ANIMATION);
  }else if (!strcmp("AT+TEMP", atCommand)){
     temperatureSensor.requestTemperatures();
     Serial.print("+TEMP=");
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