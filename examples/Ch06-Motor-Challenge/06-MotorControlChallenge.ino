// Iris Motor Control Challenge
///////////////////////////////////////////////////////////
// When the pushbutton is pressed, drive the robot in a square, trying to end up as close to the starting location as possible
// Note that your results may vary due to Surface roughness, Battery level, and/or motor differences.
// Surface roughness and battery level will especially affect the turns.
// Motor Differences may cause adjustments to be required for straight motions
// Areas that might need adjustment are noted below

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

void setup() {
}

void squreCorner(){
  robot.setMotors(-50,50);          // Turn in place              (Adjusting this will change the speed of the turn)
  delay(600);                       // Turn for 500 milliseconds  (Adjusting this will change the duration of the turn)
  robot.setMotors(0,0);             // Stop all motors
  delay(500);                       // Wait for 500 milliseconds  
}
void squareEdge(){
  robot.setMotors(100,100);       // Drive forwards               (Adjusting this so they are not the same may be required)
  delay(1000);                    // Continue for 1000 milliseconds
  robot.setMotors(0,0);           // Stop both motors
  delay(500);                     // Pause for 500 milliseconds
}

void loop() {
  if(robot.getButtonState()){       // Read the current state of the button
    delay(1000);                    // Wait for one second before moving
    squareEdge();                   // Side #1
    squreCorner();                  // Corner #1
    squareEdge();                   // Side #2
    squreCorner();                  // Corner #2
    squareEdge();                   // Side #3
    squreCorner();                  // Corner #3
    squareEdge();                   // Side #4
    squreCorner();                  // Corner #4 - You are back near the starting place
  }
  delay(100);                       // Wait for 100 milliseconds between checking the button
}
