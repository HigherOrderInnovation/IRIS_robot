// IRIS LED Blink

#include <IRIS.h>           // Import the IRIS Library
IRIS robot;                 // Create an IRIS Object

void setup() {
}

// the loop routine runs over and over again forever:
void loop() {
  robot.setLED(true);       // Turn the LED ON     
  delay(1000);              // wait for 1000 milliseconds
  robot.setLED(false);      // Turn the LED OFF
  delay(1000);              // wait for 1000 milliseconds
}
