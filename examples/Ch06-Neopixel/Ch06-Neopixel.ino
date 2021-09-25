// IRIS Chapter 6 - Neopixel
/////////////////////////////////////
// Purpose
//   Show basic functionality of the two Neopixels on the Iris Board

// Required Libraries - Add through Sketch->Include Libraries->Manage Libraries...
// 1. Adafruit_NeoPixel.h

// Required Topics
// 1. Adafruit_NeoPixel.h (https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels?gclid=Cj0KCQjwkbuKBhDRARIsAALysV6F_DMb1YGIqQJBiAr1ltKBvHXhsoXEHaZtcmq4mr7BnZY7ViTq07kaAtUSEALw_wcB)

#include <IRIS.h>   // Include the Iris library
IRIS robot;         // Create an instance of the Iris Robot

#include <Adafruit_NeoPixel.h>
#define LED_PIN    robot.getNeoPin()
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 2
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Open up the Serial Terminal
  // Tools->Serial Monitor and select 115200 for the baud rate
  Serial.begin(115200);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // Set each of the two lights
  // Red, Green, Blue, Rainbow
  strip.setPixelColor(0, strip.Color(255,0,0)); //Red
  strip.setPixelColor(1, strip.Color(255,0,0)); //Red
  strip.show();
  delay(500);
  strip.setPixelColor(0, strip.Color(0,255,0)); // Green
  strip.setPixelColor(1, strip.Color(0,255,0)); // Green 
  strip.show();
  delay(500);
  strip.setPixelColor(0, strip.Color(0,0,255)); // Blue
  strip.setPixelColor(1, strip.Color(0,0,255)); // Blue
  strip.show();
  delay(500);
  rainbow(10);
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
