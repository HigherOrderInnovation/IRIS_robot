// IRIS Chapter 4 - Light
/////////////////////////////////////
// Purpose:
//   Read the intensity of light reading from the sensor
//   Display the light reading on the serial monitor

// Required Topics:
// 1. robot.getLightReading() will return a value proportional to the light intensity

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

void setup() {
  Serial.begin(9600);       // Begin Serial communication at 9600 baud
  // Open the Serial Monitor using the magnifying glass in the upper right corner
}

void loop() {
  int lightSensorReading = robot.getLightReading();   // Read the light sensor on the robot
  String output = "Light Reading is: ";               // Assemble the output message
  output += lightSensorReading;                       // += adds the variable to the message
  Serial.println(output);
  delay(500);                                         // Delay 500ms between readings
}
