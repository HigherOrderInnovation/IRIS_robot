// IRIS Chapter 6 - Motors
//////////////////////////
// Purpose
//   When the pushbutton is pressed, drive forward and back

// Required Topics
// 1. robot.getButtonState() will return a state of the button
// 2. delay(int milliseconds); will wait the indicated number of milliseconds
// 3. robot.setMotors(int left, int right) left and right range from -100....100 with 0 being stop

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

void setup() {
}

void loop() {
  if(robot.getButtonState()){       // Read the current state of the button
    delay(1000);                    // Wait for one second before moving
    robot.setMotors(-100,-100);     // Drive backwards Left = -100 and Right = -100
    delay(1000);                    // Continue for 1000 milliseconds
    robot.setMotors(0,0);           // Stop both motors
    delay(1000);                    // Pause for 1000 milliseconds
    robot.setMotors(100,100);       // Drive forward Left = 100 and Right = 100
    delay(1000);                    // Continue for 1000 milliseoncds
    robot.setMotors(0,0);           // Stop both motors
  }
  delay(100);                       // Wait for 100 milliseconds between checking the button
}
