// IRIS Chapter 9 - IR - Purpose
/////////////////////////////////////
// Purpose
//   Turn the center LED on and off using the remote control input

// Required Libraries - Add through Sketch>Include Libraries>Manage Libraries...
// 1. IRremote.h

#include <IRIS.h>     // Include the Iris library
IRIS robot;    
       
#include <IRremote.h> // Include the IR decoding library
IRrecv irrecv(robot.getIrPin(),13);   // Initialize the IR receiver
decode_results results;

void setup()
{
  Serial.begin(9600);   // Begin serial communication
  irrecv.enableIRIn();  // Start the receiver
}

int lastMessageTime;  // Keep track of the last time a message was recevied

void loop() {
   if (millis() - lastMessageTime > 100) {  // If it has been longer than 100 milliseconds from the last message
    robot.setMotors(0,0);    // Stop the movement
  } 
  if (irrecv.decode()) {
// Print the result to the serial monitor  
// Use this to find the correct message for each button
    Serial.println(irrecv.decodedIRData.command);

    if (irrecv.decodedIRData.command == 25) { // UP arrow button
      robot.setMotors(100,100);                // Set the motors to go forward
      lastMessageTime = millis();
    }
    if (irrecv.decodedIRData.command == 28) { // DOWN arrow button
      robot.setMotors(-100,-100);      // Set the motors to go backwards
      lastMessageTime = millis();
    }  
    if (irrecv.decodedIRData.command == 12) { // LEFT arrow button
      robot.setMotors(-50,50);                 // Set the motors to turn left
      lastMessageTime = millis();
    }
    if (irrecv.decodedIRData.command == 94) { // RIGHT arrow button
      robot.setMotors(50,-50);                // Set the motors to turn right
      lastMessageTime = millis();
    }       
    if (irrecv.decodedIRData.command == 24) { // CENTER button
      robot.setMotors(0,0);                // Stop the motors
      lastMessageTime = millis();
    }    
    irrecv.resume(); // Receive the next value
  }
  delay(100);       // Slow down the loop to allow the IR receiver to reset
} 
