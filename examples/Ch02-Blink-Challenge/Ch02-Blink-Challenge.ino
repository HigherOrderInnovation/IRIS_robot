// IRIS Chapter 2 - Blink Challenge
/////////////////////////
// Purpose:
//   Blink the Blue LED on the Iris Robot for a half second longer each time

// Required Topics:
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. delay(int milliseconds); will wait the indicated number of milliseconds

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

void setup() {
  // Nothing needed here
}

int duration = 500; // Declare the variable called duration
                    // Give it an initial value of 500

void loop() {
  robot.setLED(true);         // Turn the center LED ON
  delay(duration);            // Use the variable duration
  robot.setLED(false);        // Turn the center LED OFF
  delay(500);                 // Wait for 500 milliseconds
  duration = duration + 500;  // Assign the variable duration a new value
  // Return to top of loop() and repeat forever
}
