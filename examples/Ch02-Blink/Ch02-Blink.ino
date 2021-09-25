// IRIS Chapter 2 - Blink
/////////////////////////
// Purpose
//   Blink the Blue LED on the Iris Robot

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. delay(int milliseconds); will wait the indicated number of milliseconds

#include <IRIS.h>   // Import the IRIS Library
IRIS robot;         // Create an Iris Object called robot

void setup() {
  // Nothing needed here
}

void loop() {
  robot.setLED(true);   // Turn the center LED ON
  delay(500);           // Wait for 500 milliseconds
  robot.setLED(false);  // Turn the center LED OFF
  delay(500);           // Wait for 500 milliseconds
  // Return to top of loop() and repeat forever
}
