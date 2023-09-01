// IRIS IR Motor Control
/////////////////////////////////////
// Purpose
//   Use the UP, DOWN, LEFT, RIGHT, and Center buttons on a IR remote to drive the robot around the table.
//
// NOTES
// 1. All styles of IR remotes are different.  Open the terminal with this program running to see the received codes to adjust below.
// 2. To make the motors run, 2xAA batteries will be needed.
// 3. It is recommended to attach the front leg to the robot for driving.

// Required Libraries - Add through Sketch>Include Libraries>Manage Libraries...
// 1. IRremote.h - This was built against Version 2.2.3

#include <IRIS.h>     // Include the Iris library
IRIS robot;

#include <IRremote.h> // Include the IR decoding library
IRrecv irrecv(robot.getIrPin(), 13);  // Initialize the IR receiver
decode_results results;

void setup()
{
  Serial.begin(9600);   // Begin serial communication
  irrecv.enableIRIn();  // Start the receiver
}

int lastMessageTime;  // Keep track of the last time a message was recevied
int leftValue = 0, rightValue = 0;
void loop() {
  
  // This can be uncommented to help with run-away robots
  //if (millis() - lastMessageTime > 100) {  // If it has been longer than 100 milliseconds from the last message
  // robot.setMotors(0,0);    // Stop the movement
  //}
  
  if (irrecv.decode(&results)) {
    // Print the result to the serial monitor
    // Use this to find the correct message for each button
    Serial.println(results.value);

    if (results.value == 16730805) { // DOWN arrow button
      // Set the targets for each motor.  Range -100...0...100
      rightValue = 100;
      leftValue = 100;
      // Record the last message time if you engage the run-away robot check above
      lastMessageTime = millis();
    }
    if (results.value == 16718055) { // UP arrow button
      rightValue = -100;
      leftValue = -100;
      lastMessageTime = millis();
    }
    if (results.value == 16716015) { // LEFT arrow button
      rightValue = 50;
      leftValue = -50;
      lastMessageTime = millis();
    }
    if (results.value == 16734885) { // RIGHT arrow button
      rightValue = -50;
      leftValue = 50;
      lastMessageTime = millis();
    }
    if (results.value == 16726215) { // CENTER button
      rightValue = 0;
      leftValue = 0;
      lastMessageTime = millis();
    }
    robot.setMotors(rightValue, leftValue); // Use the set values to turn the motors on
    irrecv.resume(); // Receive the next value
  }
  delay(100);       // Slow down the loop to allow the IR receiver to reset
}
