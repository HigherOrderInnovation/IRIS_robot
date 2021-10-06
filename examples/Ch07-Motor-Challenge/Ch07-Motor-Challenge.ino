// IRIS Chapter 6 - Motors - Challenge
//////////////////////////
// Challenge
//   When the pushbutton is pressed, drive the robot in a square, trying to end up as close to the starting location as possible

// Required Topics
// 1. robot.setMotors(int left, int right) left and right range from -100....100 with 0 being stop


#include <IRIS.h>   
IRIS robot;         

void setup() {
}

void squareCorner(){
  robot.setMotors(-50,50);          // Adjusting this will change the speed of the tur
  delay(600);                       // Adjusting this will change the duration of the tur
  robot.setMotors(0,0);             // Stop all motors
  delay(500);                       // Wait for 500 milliseconds  
}
void squareEdge(){
  robot.setMotors(100,100);       // Adjusting this so they are not the same may be required
  delay(1000);                    // Continue for 1000 milliseconds
  robot.setMotors(0,0);           // Stop both motors
  delay(500);                     // Pause for 500 milliseconds
}

void loop() {
  if(robot.getButtonState()){       // Read the current state of the button
    delay(1000);                    // Wait for one second before moving
    squareEdge();                   // Side #1
    squareCorner();                 // Corner #1
    squareEdge();                   // Side #2
    squareCorner();                 // Corner #2
    squareEdge();                   // Side #3
    squareCorner();                 // Corner #3
    squareEdge();                   // Side #4
    squareCorner();                 // Corner #4 - You are back near the starting place
  }
  delay(100);                       // Wait for 100 milliseconds between checking the button
}
