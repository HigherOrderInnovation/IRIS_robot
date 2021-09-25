// Iris Chapter 3 - Button - Challenge
//////////////////////////////////////
// Challenge
//   When the blue LED turns ON, how long does it take you to push the button?

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. robot.getButtonState() returns true (pressed) or false (released) for the state of the button.
// 3. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)
// 4. delay(int milliseconds) wait a certain amount of time.
// 5. random(int start, int end) will produce a random integer between start and end (inclusive)
// 6. while loop (https://www.arduino.cc/reference/en/language/structure/control-structure/while/)

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

void setup() {
  Serial.begin(9600); // Begin the Serial Communication at 9600 baud
}

void loop() {
  Serial.println("When the light flashes, press the button.");
  int randomDelay = random(1000,5000);  // Generate a random number between 1000 and 5000
  delay(randomDelay);             // Wait for the random delay
  robot.setLED(false);             // Turn the LED ON 
  long testStartTime = millis();  // Record when the LED turns on
  while(true){                    // Loop forever
    if(robot.getButtonState()){
      break;                      // Break out of the while loop
    }
  }
  long testEndTime = millis();    // Record when the button is pressed
  // Print out the results of the game
  Serial.print("The light was delayed by ");
  Serial.print(randomDelay);
  Serial.println(" milliseconds");
  if(testEndTime-testStartTime == 0){
    Serial.println("False Start - You pressed the button too early.");
  }
  else{
    Serial.print("It took you ");
    Serial.print(testEndTime-testStartTime);
    Serial.println(" milliseconds to react.");
  }
  delay(1000);
  Serial.println();               // Create a blank line
  Serial.println("Press the button to play again");
  while(true){                    // Loop forever
    if(robot.getButtonState()){
      break;                      // Break out of the while loop
    }
  }
  robot.setLED(true);             // Turn the LED OFF
}
