// IRIS Chapter 10 - Bluetooth - Challenge
/////////////////////////////////////
// Challenge
//   Connect the Iris robot to the Higher Order Innovation Apollo Remote Control Android App (available in the Play Store)
//   Remember to pair your Iris robot with your phone through the Android Bluetooth Menu at the top of your screen
//   Once connected button commands will be sent from the phone to the robot and feedback sent from your robot to the phone
//   Using the in-app slider, control the brightness of the NeoPixels

// Required Topics:
// 1. Arrays - (https://www.arduino.cc/reference/en/language/variables/data-types/array/)

#include "BluetoothSerial.h"    // This Library allows for Serial Communication between the Robot and your Phone
BluetoothSerial SerialBT;       // Create a BluetoothSerial Object named SerialBT

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

// Additional set-up required for Neopixel
#include <Adafruit_NeoPixel.h>
#define LED_PIN    robot.getNeoPin()
#define LED_COUNT 2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Remote Control Input
// Index  Mapping     Description
//   0    Button A    1 if pressed, 0 if released
//   1    Button B    1 if pressed, 0 if released
//   2    Button X    1 if pressed, 0 if released
//   3    Button Y    1 if pressed, 0 if released
//   4    Trackpad X  Range from -100 to 100 for horizontal tracking
//   5    Trackpad Y  Range from -100 to 100 for vertical tracking
//   6    Slider      Range from 0 to 100

// For example remote[3] represents the fourth value in the array (numbering starts from 0) and corresponds to the button marked X in the app
int remote[] = {0, 0, 0, 0, 0, 0, 0};
boolean stringComplete = false; // This flag is used to indicate when a full message is received
String inputString = "";        // This String holds the message as it is being read
char tempChar[5];               // This is a buffer that helps in converting the incoming message to integers to go into remote[]

#include "esp_bt_main.h"
#include "esp_bt_device.h"


void setup() {
  // Start Bluetooth Advertising so that your phone can see it
  // You can name the robot nearly anything by replacing Iris below
  SerialBT.begin("Iris");
  
  Serial.begin(115200);       // Begin Serial communication at 115200 baud
// Open the Serial Monitor using the magnifying glass in the upper right corner

// Initialize NeoPixel strip object
  strip.begin();           
  strip.show();
}

int counter = 0;
void readRemoteInput() {
  // While there are characters waiting to be read
  while (SerialBT.available()) {
    // Read the next character
    char inChar = (char)SerialBT.read();
    // Handle the end of the message (The phone ends the message with a '.')
    if (inChar == '.') {
      stringComplete = true;
    }
    else if (inChar == ',') { // Each time a comma is hit, save the previous value
      // Convert the String to charArray
      inputString.toCharArray(tempChar, 5);
      // Using the function atoi, convert the charArray to an integer
      remote[counter] = atoi(tempChar);
      // Clear the inputString for the next number
      inputString = "";
      // increment the counter to the next position in remote[]
      counter++;
    }
    else {
      // If not the end of a value (,) or the end of the message (.), add the incoming character to the end of inputString 
      inputString += inChar;
    }
  }

  // Each Time there is a new message, this will trigger
  if (stringComplete) {
    // Reset the end of message flag
    stringComplete = false;
    // Reset the counter that iterates through the remote[] array
    counter = 0;
  }
}

// Keep track of the last message that was printed to the screen
int lastMessagePrintTime = 0;

void loop() {
  // Check for incoming messages
  readRemoteInput();

  // Every 100 milliseconds, print out the most recent message and act on it
  if (millis() - lastMessagePrintTime > 100) {
    // Update the lastMessagePrintTime to the current milliseconds count
    lastMessagePrintTime = millis();
    // Print out all of the incoming values from the remote
    Serial.print("[");
    for (int i = 0; i < 7 ; i = i + 1) {
      Serial.print(remote[i]);
      if (i != 6) { // Add a comma for readability on all but the last
        Serial.print(",");
      }
    }
    Serial.println("]");

    // Convert the 0-100 value from the slider to the expected 0-255 range for brightness
    int mappedBrightness = map(remote[6],0,100,0,255);

    uint32_t color = strip.Color(255,0,0);  // Choose the color here.

    strip.setBrightness(mappedBrightness);  // Set the new brightness           
    strip.setPixelColor(0, color);          // Use the color variable set above
    strip.setPixelColor(1, color);          // Use the color variable set above
    strip.show();                           // Display the new colors
  }
  
  delay(5); // Slow down reading.
}
