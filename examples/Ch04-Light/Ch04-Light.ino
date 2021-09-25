// IRIS Chapter 4 - Light
/////////////////////////////////////
// Purpose
//   Read the intensity of light reading from the sensor
//   Display the light reading on the screen

// Required Topics
// 1. robot.getLightReading() will return a value proportunal to the light intensity
// 2. delay(int milliseconds); will wait the indicated number of milliseconds
// 3. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

void setup() {
  Serial.begin(9600);       // Begin Serial communication at 9600 baud
}

void loop() {
  int lightSensorReading = robot.getLightReading();   // Read the light sensor on the robot
  String output = "Light Reading is: ";               // Assemble the output message
  output += lightSensorReading;
  Serial.println(output);
  delay(500);                                         // Delay 500ms between readings
}
