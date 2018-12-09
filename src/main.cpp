#include <Arduino.h>
#include "USART.h"

Usart usart;
String rxString;
void rxParse(String str);

void setup() {
  // put your setup code here, to run once:
  usart.setOnReceiveCallback(&rxParse);
  Serial.begin(9600);
  Serial.println("Test");
}

void loop() {
  // put your main code here, to run repeatedly:
  usart.usartEvent(rxString);
}

void rxParse(String str) {

  char buf[256];
  str.toCharArray(buf, str.length());
  char *atCommand = strtok(buf, "=,?");
  Serial.println(str);

  if (!strcmp("AT+HSVROT", atCommand)) {
    char *rotationTimeStr = strtok(NULL, ",");
    uint16_t rotationTime = atoi(rotationTimeStr);
    Serial.print("Rotation speed: ");
    Serial.println(rotationTime);
  }else if (!strcmp("AT+RGB", atCommand)){
    
  }
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