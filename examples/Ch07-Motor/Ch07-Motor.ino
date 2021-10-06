// IRIS Chapter 6 - Motors
//////////////////////////
// Purpose
//   When the pushbutton is pressed, drive forward and back

// Required Topics
// 1. robot.setMotors(int left, int right) left and right range from -100....100 with 0 being stop

#include <IRIS.h> 
IRIS robot;      

void setup() {
}

void turn(int turnDuration){
  robot.setMotors(-50,50);          // Adjusting will change speed of turn
  delay(turnDuration);              // Adjusting will change duration of turn
  robot.setMotors(0,0);             // Stop all motors
  delay(500);                       // Wait for 500 milliseconds  
}

void loop() {
  if(robot.getButtonState()){       // Read the current state of the button
    delay(1000);                    // Wait for one second before moving
    robot.setMotors(-100,-100);     // Drive backwards Left = -100, Right = -100
    delay(1000);                    // Continue for 1000 milliseconds
    robot.setMotors(0,0);           // Stop both motors
    delay(1000);                    // Pause for 1000 milliseconds
    robot.setMotors(100,100);       // Drive forward Left = 100 and Right = 100
    delay(1000);                    // Continue for 1000 milliseconds
    robot.setMotors(0,0);           // Stop both motors
    turn(500);                      // Turn for 500 milliseconds
  }
  delay(100);                       // Wait for 100 milliseconds 
}
