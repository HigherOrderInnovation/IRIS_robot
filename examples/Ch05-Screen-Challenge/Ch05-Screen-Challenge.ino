// IRIS Chapter 5 - Screen
/////////////////////////////////////
// Purpose
//   Use the screen to communicate the light sensor reading

// Required Libraries
// 1. Adafruit_GFX
// 2. Adafruit_SSD13067

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot
//This allows Arduino to talk to the Iris robot you have plugged in to the computer.

// Additional Include statements for screen libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// These functions are required to initialize the screen
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();     
  display.setTextColor(SSD1306_WHITE);  
}

void loop() {
  if (robot.getButtonState()) { // Check the state of the button
     int lightSensorReading = robot.getLightReading(); // Read the light sensor
     String output = "Light Reading: ";                // Assemble the output message
      output += lightSensorReading;
      display.clearDisplay();                           // Clear the Screen
      display.setTextSize(1);                           // Normal 1:1 pixel scale
      display.setCursor(0,0);                           // Start at top-left corner
      display.println(output);                          // Print to screen then create a new line
      display.display();                                // Render the screen
      delay(500);                                       // Delay 500 ms
  }

  else {
     display.clearDisplay();     // Clear the Screen
     display.display();          // Render the screen
  }
}
