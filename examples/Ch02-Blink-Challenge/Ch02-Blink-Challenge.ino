// IRIS Chapter 2 - Blink - Challenge
/////////////////////////////////////
// Challenge
//   Create a first function that takes an integer number of milliseconds and
//     blinks the LED for that time
//   Create a second function that takes two inputs and returns their sum

// Required Topics
// 1. robot.setLED(bool state) will turn the light on (true) or off (false)
// 2. delay(int milliseconds); will wait the indicated number of milliseconds
// 3. Serial Communication and Serial Terminal (https://www.arduino.cc/reference/en/language/functions/communication/serial/)
// 4. Functions (https://www.arduino.cc/en/Reference/FunctionDeclaration)

#include <IRIS.h>           // Import the IRIS Library
IRIS robot;                 // Create an Iris Object called robot

void setup() {
  Serial.begin(9600);       // Begin Serial communication at 9600 baud
}

void blinkLED(int durationOfBlink){
  robot.setLED(true);       // Turn the LED ON     
  delay(durationOfBlink);   // wait for the specified length of time
  robot.setLED(false);      // Turn the LED OFF
}

int addTwoIntegers(int x, int y){
  // Optionally do something with x and y
  return x+y;
}

// the loop routine runs over and over again forever:
void loop() {
  blinkLED(250);            // Blink the LED for X milliseconds
  delay(2000);              // wait for 2000 milliseconds
  Serial.println("500 + 1000 = 1500");
  int result = addTwoIntegers(500,1000);  // Call the function and save the returned value
  Serial.print("500 + 1000 = ");
  Serial.println(result);   // Print the result of the function
  Serial.println();         // Add a blank line
}
