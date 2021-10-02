// Iris Chapter 3 - Button
//////////////////////////
// Purpose
//  When the button is pressed, turn the LED on.  Print to the serial monitor how long the button was pressed.

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. robot.getButtonState() returns true (pressed) or false (released) for the state of the button.
// 3. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)


#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

long stopLED;
long startLED;

void setup() {
  Serial.begin(9600); // Begin the Serial Communication at 9600 baud
}

void loop() {
  if (robot.getButtonState()) { // Check the state of the button
    robot.setLED(true);         // Turn on the LED
    startLED = millis();  // Record when the LED turns on
    while (true) {                  // Loop until broken
      if (!robot.getButtonState()) {
        break;                      // Break out of the while loop when the button is released
      }
    }
    stopLED = millis();    // Record when the button is let go
    Serial.print("The button was on for ");
    Serial.print(stopLED - startLED);
    Serial.println(" milliseconds.");
    delay(10);
  }
  else {
    robot.setLED(false);        // Turn off the LED
  }
}
