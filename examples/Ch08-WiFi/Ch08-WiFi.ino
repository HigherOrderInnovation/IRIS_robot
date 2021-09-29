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
IRIS robot;         // Create an instance of the Iris Robot

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
            client.print("<br><br>Click <a href=\"/H\">here</a> to turn ON the LED.<br><br><br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

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

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          robot.setLED(true);
        }
        if (currentLine.endsWith("GET /L")) {
          robot.setLED(false);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
