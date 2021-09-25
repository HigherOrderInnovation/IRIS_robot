// IRIS OLED Output Screen
// Requires Adafruit_SSD1306 library
// Install through Sketch->Include Libraries->Manage Libraries

#include <IRIS.h>
IRIS robot;

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

void loop() {
  // Read the light sensor on the robot. 
  // The value is 0-4095
  int lightSensorReading = robot.getLightReading();
  
  String output = "Light Reading: ";       // Assemble the output message
  output += lightSensorReading;
  
  display.clearDisplay();                     // Clear the Screen
  display.setTextSize(1);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);                     // Start at top-left corner
  display.println(output);                    // Show the same output on the screen
  display.display();                          // Render the screen
  Serial.println(output);                     // Show the output in ther Serial Terminal
  // Delay 500ms between readings
  delay(500);
}
