// Iris Chapter 3 - Button
//////////////////////////
// Purpose
//  When the button is pressed, turn the LED on.

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. robot.getButtonState() returns true (pressed) or false (released) for the state of the button.
// 3. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

void setup() {
}

void loop() {
  if(robot.getButtonState()){   // Check the state of the button
    robot.setLED(true);         // Turn on the LED
  }
  else{
    robot.setLED(false);        // Turn off the LED
  }

}
