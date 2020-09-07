// IRIS LED Blink

#include <IRIS.h>

IRIS robot;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  robot.setLED(true);
  delay(500);
  robot.setLED(false);
  delay(500);
}
