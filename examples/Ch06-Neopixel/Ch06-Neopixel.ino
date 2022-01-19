// IRIS Chapter 6 - Neopixel
/////////////////////////////////////
// Purpose
//   Fade Neopixel LEDs

// Required Libraries 
// 1. Adafruit_NeoPixel.h

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot

// Additional set-up required for Neopixel
#include <Adafruit_NeoPixel.h>
#define LED_PIN    robot.getNeoPin()
#define LED_COUNT 3
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {    // Initialize NeoPixel strip object
  strip.begin();           
  strip.show();   
  strip.setBrightness(100);  
}

uint32_t color = strip.Color(0,0,0);  // Choose the color here.

void loop() {
  for (int i = 0; i <= 255; i = i+5){     // The variable i will INCREASE from 0 to 50 by an increment of 1
    color = strip.Color(i,0,0);          
    strip.setPixelColor(0, color);      // Use the color variable
    strip.setPixelColor(1, color);      // Use the color variable
    strip.setPixelColor(2, color);      // Use the color variable
    strip.show();                       // Display the new colors
    delay(50);                          // Wait 50 milliseconds
  }
// Reverse the fading sequence:
  for (int i = 255; i >= 0; i = i-5){     // The variable i will DECREASE from 50 to 0 by an increment of 1
    color = strip.Color(i,0,0);             
    strip.setPixelColor(0, color);      // Use the color variable
    strip.setPixelColor(1, color);      // Use the color variable
    strip.setPixelColor(2, color);      // Use the color variable
    strip.show();                       // Display the new colors
    delay(50);                          // Wait 50 milliseconds
  }
}
