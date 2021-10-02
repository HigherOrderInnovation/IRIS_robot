// Iris Chapter 3 - Button
//////////////////////////
// Purpose
//  When the button is pressed, turn the LED on.  Use the serial monitor to print whether the LED is on or off.

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. robot.getButtonState() returns true (pressed) or false (released) for the state of the button.

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

void setup() {
  Serial.begin(9600); // Begin the Serial Communication at 9600 baud
  // Open the Serial Monitor using the magnifying glass in the upper right corner
}

void loop() {
  if (robot.getButtonState()) {       // Check the state of the button
    robot.setLED(true);               // If the button is TRUE then the LED turns on
    Serial.println("The LED is on");  // Print a new line to the Serial Monitor
  }
  else {
    robot.setLED(false);              // If the button is FALSE then the LED turns off
    Serial.println("The LED is off"); // Print a new line to the Serial Monitor
  }
  delay(10);  // This delay is necessary for the button to reset
}
