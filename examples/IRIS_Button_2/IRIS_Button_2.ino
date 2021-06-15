// IRIS Button Testing Step 2
// A true/false boolean flag is used to detect when the button is released

#include <IRIS.h>           // Import the IRIS Library
IRIS robot;                 // Create an IRIS Object

int buttonCounter = 0;      // Create an integer variable and initialize it to 0
bool isButtonToggled = false; // Create a true/false to store the last state of the button

void setup() {
  delay(500);               // Wait 500 milliseconds
  Serial.begin(115200);     // Start Serial communication with the computer at 115200 baud
                              // Baud rate is the speed at which the communication will happen
  Serial.println("Button Test");  // Send "Button Test" to the computer
}

void loop() {
  if(robot.getButtonState() == 1){  // The Button is a digital signal and is either a 1(HIGH/TRUE) or a 0(LOW/FALSE)
    if(isButtonToggled){            // The Button must be released for this to be true.
      isButtonToggled = false;      // Record that the button has been pressed
      buttonCounter++;              // Increment the counter
      Serial.print("Button Counter ");  // Print text to the screen
      Serial.println(buttonCounter);    // Print the value of the variable
    }
  }
  else{
    isButtonToggled = true;         // Record that the button was released
  }
  delay(50);
}
