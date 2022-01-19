// IRIS Chapter 6 - Neopixel
/////////////////////////////////////
// Purpose
//   Cycle through the rainbow using the Neopixels

// Required Libraries 
// 1. Adafruit_NeoPixel.h

#include <IRIS.h>   // Import the Iris library
IRIS robot;         // Create an Iris object called robot

// Additional set-up required for Neopixel
#include <Adafruit_NeoPixel.h>
#define LED_PIN    robot.getNeoPin()
#define LED_COUNT 3
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // Initialize NeoPixel strip object
  strip.show();            
  strip.setBrightness(50); // Set brightness to about 20% (max = 255)
}

void loop() {
  for(int i = 0; i<=255; i=i+5){        // Red -> Yellow
    strip.setPixelColor(0, strip.Color(255,i,0)); 
    strip.setPixelColor(1, strip.Color(255,i,0)); 
    strip.setPixelColor(2, strip.Color(255,i,0)); 
    strip.show();
    delay(50);
    }
  for(int i = 255; i>=0; i=i-5){        // Yellow -> Green
    strip.setPixelColor(0, strip.Color(i,255,0)); 
    strip.setPixelColor(1, strip.Color(i,255,0)); 
    strip.setPixelColor(2, strip.Color(i,255,0)); 
    strip.show();
    delay(50);
    }
  for(int i = 0; i<=255; i=i+5){        // Green -> Cyan
    strip.setPixelColor(0, strip.Color(0,255,i)); 
    strip.setPixelColor(1, strip.Color(0,255,i)); 
    strip.setPixelColor(2, strip.Color(0,255,i)); 
    strip.show();
    delay(50);
   }
  for(int i = 255; i>=0; i=i-5){        // Cyan -> Blue
    strip.setPixelColor(0, strip.Color(0,i,255)); 
    strip.setPixelColor(1, strip.Color(0,i,255)); 
    strip.setPixelColor(2, strip.Color(0,i,255)); 
    strip.show();
    delay(50);
    }
   for(int i = 0; i<=255; i=i+5){        // Blue -> Magenta
    strip.setPixelColor(0, strip.Color(i,0,255)); 
    strip.setPixelColor(1, strip.Color(i,0,255)); 
    strip.setPixelColor(2, strip.Color(i,0,255)); 
    strip.show();
    delay(50);
    }
    for(int i = 255; i>=0; i=i-5){        // Magenta -> Red
    strip.setPixelColor(0, strip.Color(255,0,i)); 
    strip.setPixelColor(1, strip.Color(255,0,i)); 
    strip.setPixelColor(2, strip.Color(255,0,i)); 
    strip.show();
    delay(50);
    }
}
