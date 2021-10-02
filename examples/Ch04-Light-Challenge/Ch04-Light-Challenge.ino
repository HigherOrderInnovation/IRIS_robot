// IRIS Light Sensor - Challenge
/////////////////////
// 1. Read the value of the Light Sensor
// 2. Proportionately convert the light reading to a delay for the LED to blink

// Required Topics
// 1. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)
// 2. The 'map' function (https://www.arduino.cc/reference/en/language/functions/math/map/0

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

void setup() {
  Serial.begin(9600);       // Begin Serial communication at 9600 baud
}

void loop() {
  int light = robot.getLightReading();      // Read the light sensor
  Serial.print("The light reading is ");
  Serial.println(light);
  int blinkRate = map(light, 0, 4095, 5, 1000);  // Proportionately map the sensor to a delay range
  Serial.print("The blink rate is ");
  Serial.println(blinkRate);
  delay(blinkRate);                              // Wait for the calculated time
  robot.setLED(true);                       // Turn on the LED
  delay(blinkRate);                              // Wait for the calculated time
  robot.setLED(false);                      // Turn off the LED
}
