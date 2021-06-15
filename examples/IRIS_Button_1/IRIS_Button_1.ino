// IRIS Button Testing

#include <IRIS.h>           // Import the IRIS Library
IRIS robot;                 // Create an IRIS Object

int buttonCounter = 0;      // Create an integer variable and initialize it to 0

void setup() {
  delay(500);               // Wait 500 milliseconds
  Serial.begin(115200);     // Start Serial communication with the computer at 115200 baud
                              // Baud rate is the speed at which the communication will happen
  Serial.println("Button Test");  // Send "Button Test" to the computer
}

void loop() {
  // The Button is a digital signal and is either a 1(HIGH/TRUE) or a 0(LOW/FALSE)
  if(robot.getButtonState() == 1){  // If the state is equal to 1
    buttonCounter++;                // Add one to the integer variable.  This is the same as 
                                      // buttonCounter = buttonCounter + 1      
    Serial.print("Button Counter ");    // Print this text to the computer
    Serial.println(buttonCounter);      // Print the current value of the variable
  }
  delay(50);                            // Wait for 50 milliseconds
}
