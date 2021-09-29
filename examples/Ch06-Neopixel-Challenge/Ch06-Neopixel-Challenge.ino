// IRIS Chapter 6 - Neopixel - Challenge
/////////////////////////////////////
// Challenge
//   Display purple light on both LEDs
//   Fade those LEDs from full ON to OFF over 3 seconds and then reverse the fade from OFF to ON

// Required Libraries - Add through Sketch->Include Libraries->Manage Libraries...
// 1. Adafruit_NeoPixel.h

// Required Topics
// 1. Adafruit_NeoPixel.h (https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels?gclid=Cj0KCQjwkbuKBhDRARIsAALysV6F_DMb1YGIqQJBiAr1ltKBvHXhsoXEHaZtcmq4mr7BnZY7ViTq07kaAtUSEALw_wcB)
// 2. for loop (https://www.arduino.cc/reference/en/language/structure/control-structure/for/)

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

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to maximum so we can control it later
}

void loop() {
  for (int i = 0; i <= 255; i = i+5){           // The variable i will go from 0 to 255 in increments of 5 for a total of 52 iterations
    strip.setPixelColor(0, strip.Color(i,0,i)); // Purple
    strip.setPixelColor(1, strip.Color(i,0,i)); // Purple
    strip.show();                               // Display the new colors
    delay(3000/52);                             // wait to make the whole fade 5 seconds long
  }
  // Reverse the fading sequence
  for (int i = 255; i >= 0; i = i-5){           // The variable i will go from 255 to 0 in increments of 5 for a total of 52 iterations
    strip.setPixelColor(0, strip.Color(i,0,i)); // Purple
    strip.setPixelColor(1, strip.Color(i,0,i)); // Purple
    strip.show();                               // Display the new colors
    delay(3000/52);                             // wait to make the whole fade 5 seconds long
  }
}
