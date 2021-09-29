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

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
