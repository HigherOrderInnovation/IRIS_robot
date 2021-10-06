// IRIS Chapter 8 - WiFi 
////////////////////////
// Pupose
//   Create an access point with Iris
//   Using a phone/tablet/computer connect to the "Iris" wifi network
//   Open a browser (Chrome/Edge/Safari etc) and go to the webpage 192.168.4.1
//   Click on the different options to change the state of the LED

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <IRIS.h>   // Include the Iris library
IRIS robot;         

// Additional set-up required for Neopixel
#include <Adafruit_NeoPixel.h>
#define LED_PIN    robot.getNeoPin()
#define LED_COUNT 2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const char *ssid = "Iris";                        // Set the name of your WiFi network
const char *password = "password";                // Set the password of your WiFi network

WiFiServer server(80);

void setup() {
  Serial.begin(115200);                           // Start communication with a baud of 115200
  Serial.println();                               // Print a blank line
  Serial.println("Iris Access Point Test");

  //WiFi.softAP(ssid, password);        // Uncomment this line and comment out previous to add the password
  WiFi.softAP(ssid);                    // Start a network with a password that will be named ssid
  server.begin();                       // Start up the server that will handle requests

  Serial.println("Server started");     // Print out the notice of the server starting

  strip.begin();           // Initialize the Neopixels
  strip.show(); 
  strip.setBrightness(50);
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<br><br>Turn the Neopixels <a href=\"/Red\">Red</a>.<br>");
            client.print("<br><br>Turn the Neopixels <a href=\"/Yellow\">Yellow</a>.<br>");
            client.print("<br><br>Turn the Neopixels <a href=\"/Green\">Green</a>.<br>");
            client.print("<br><br>Turn the Neopixels <a href=\"/Cyan\">Cyan</a>.<br>");
            client.print("<br><br>Turn the Neopixels <a href=\"/Blue\">Blue</a>.<br>");
            client.print("<br><br>Turn the Neopixels <a href=\"/Magenta\">Magenta</a>.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

       // Check to the client request 
        if (currentLine.endsWith("GET /Red")) {
         strip.setPixelColor(0, strip.Color(255,0,0));      // Use the color variable
         strip.setPixelColor(1, strip.Color(255,0,0));      // Use the color variable
         strip.show();                                      // Display the new colors
        }
      
        if (currentLine.endsWith("GET /Yellow")) {
         strip.setPixelColor(0, strip.Color(255,255,0));      // Use the color variable
         strip.setPixelColor(1, strip.Color(255,255,0));      // Use the color variable
         strip.show();                                      // Display the new colors
        }

       if (currentLine.endsWith("GET /Green")) {
         strip.setPixelColor(0, strip.Color(0,255,0));      // Use the color variable
         strip.setPixelColor(1, strip.Color(0,255,0));      // Use the color variable
         strip.show();                                      // Display the new colors
        }
       if (currentLine.endsWith("GET /Cyan")) {
         strip.setPixelColor(0, strip.Color(0,255,255));      // Use the color variable
         strip.setPixelColor(1, strip.Color(0,255,255));      // Use the color variable
         strip.show();                                      // Display the new colors
        }
       if (currentLine.endsWith("GET /Blue")) {
         strip.setPixelColor(0, strip.Color(0,0,255));      // Use the color variable
         strip.setPixelColor(1, strip.Color(0,0,255));      // Use the color variable
         strip.show();                                      // Display the new colors
        }
       if (currentLine.endsWith("GET /Magenta")) {
         strip.setPixelColor(0, strip.Color(255,0,255));      // Use the color variable
         strip.setPixelColor(1, strip.Color(255,0,255));      // Use the color variable
         strip.show();                                      // Display the new colors
        }
           

      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
