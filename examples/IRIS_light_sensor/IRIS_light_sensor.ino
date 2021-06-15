// IRIS Light Sensor

#include <IRIS.h>           // Import the IRIS Library
IRIS robot;                 // Create an IRIS Object

void setup() {
  delay(500);               // Wait for 500 milliseconds
  Serial.begin(115200);     // Start Serial communication with the computer at 115200 baud
                              // Baud rate is the speed at which the communication will happen
  Serial.println("Light Sensor Test"); // Send "Light Sensor Test" to the computer
}

void loop() {
  int sensorValue = robot.getLightReading();          // 0-4095 is returned from the sensor
  int mappedValue = map(sensorValue, 0, 4095, 0, 100);// Proportionally map the value onto 0-100
  Serial.print("Raw Value is : ");                    // Print this text to the screen
  Serial.print(sensorValue);                          // Print the raw value
  Serial.print(" which maps to ");                    // Print this text to the screen
  Serial.print(mappedValue);                          // Print the mapped value to the screen
  Serial.println("/100");                             // Print this text to the screen
  delay(500);                                         // Wait 500 milliseconds
}
