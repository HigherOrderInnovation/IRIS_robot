// IRIS Chapter 5 - Screen - Challenge
//////////////////////////////////////
// Challenge
//   Create a progress bar that builds across the screen

// Required Libraries - Add through Sketch->Include Libraries->Manage Libraries...
// 1. Adafruit_GFX
// 2. Adafruit_SSD1306

// Required Topics
// 1. Adafruit_SSD1306.h (https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples)

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

// Additional Include statements for the Screen
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Open up the Serial Terminal
  // Tools->Serial Monitor and select 115200 for the baud rate
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay();
}
void firstProgress() {
  display.setCursor(0, 24);
  for (int i = 0; i < 20; i++) {
    display.print((char)0xDA);
    display.display();
    delay(50);
  }
}

void loop() {  
  display.clearDisplay();                     // Clear the Screen
  display.setTextSize(1);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);                     // Start at top-left corner
  display.println("Working...");              // Show the same output on the screen
  display.setCursor(0, 24);                   // Move to the bottom left corner of the screen
  for (int i = 0; i < 20; i++) {              // For each of the positions on the screen
    display.print((char)0xDA);                // Display the special character 0xDA. How can you find out what this character looks like?
    display.display();                        // Update the screen
    delay(50);                                // Create the progress bar that will last 1 second
  }
  delay(500);                                 // Delay 500 milliseconds before resetting the screen
}
