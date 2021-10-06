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
  robot.setLED(false);  // Turn the center LED off to start

}

void loop() {
  if (irrecv.decode()) {
// Print the result to the serial monitor  
// Use this to find the correct message for each button
    Serial.println(irrecv.decodedIRData.command);
    if (irrecv.decodedIRData.command == 25) { // UP arrow button
       robot.setLED(true);                    // Turn the center LED ON
    }
    if (irrecv.decodedIRData.command == 28) { // DOWN arrow button
       robot.setLED(false);                   // Turn the center LED off
    }    
    irrecv.resume(); // Receive the next value
  }
  delay(100);       // Slow down the loop to allow the IR receiver to reset
} 
