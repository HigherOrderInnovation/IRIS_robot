// IRIS Chapter 8 - IR - Challenge
/////////////////////////////////////
// Challenge
//   Read the remote control input
//   Control the motors on the robot to drive it
//   Depending on the remote that you use, you may need to adjust the values in the if statements at the bottom

// Required Libraries - Add through Sketch->Include Libraries->Manage Libraries...
// 1. IRremote.h

#include <IRremote.h> // Include the IR decoding library
#include <IRIS.h>     // Include the Iris library
IRIS robot;           // Create an instance of the Iris Robot
IRrecv irrecv(robot.getIrPin());
decode_results results;

int lastMessageTime;  // Keep track of the last time a message was recevied

void setup()
{
  Serial.begin(9600);  // Start the serial link to the computer
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  remote();
  if (millis() - lastMessageTime > 100) {  // If it has been longer than 100 milliseconds from the last message
    robot.setMotor(0,0);    // Stop the movement
  }
}

void remote() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);      // Print the result to the screen
    if (results == 0x1F) {
      //A
    }
    if (results == 0x1E) {
      //B
    }
    if (results == 0x1A) {
      //C
    }
    if (results == 0x1B) {
      //power
    }
    if (results == 0x8) {
      //left
      robot.setMotor(-50,50);       // Set the motors to turn left
      lastMessageTime = millis();
    }
    if (results == 0x1) {
      //right
      robot.setMotor(50,-50);       // Set the motors to turn right
      lastMessageTime = millis();
    }
    if (results == 0x5) {
      //forward
      robot.setMotor(100,100);      // Set the motors to go forward
      lastMessageTime = millis();
    }
    if (results == 0x0) {
      //back
      robot.setMotor(-100,-100);      // Set the motors to go backwards
      lastMessageTime = millis();
    }
    irrecv.resume();
  }
  delay(100);                         // SLow down the loop a little
}
