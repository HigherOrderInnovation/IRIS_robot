#include <PS4Controller.h>
// Use the SixAxisPairTool to reset the MAC Address target for the PS4 controller
// If trying to replace a PS4 controller, you may need to erase the flash entirely.  The command line tool is esptool.py --chip esp32 erase_flash
String targetMAC = "aa:bb:cc:dd:ee:09";
boolean isDock = true;

// Screen Code
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Servo Code
#include <ESP32Servo.h>
Servo Servo1, Servo2, Servo3, Servo4, Servo5, Servo6;
long lastUpdate = 0;

// NeoPixels
//#include <Adafruit_NeoPixel.h>
//#define LED_COUNT 3
//#define LED_PIN    6
//Adafruit_NeoPixel strip(3, robot.getNeoPin(), NEO_GRB + NEO_KHZ800);

const int freq = 10000;
const int ledChannel = 12;
const int ledChannel2 = 13;
const int resolution = 8;

int M1 = 32;
int M2 = 33;
int M3 = 27;
int M4 = 15;
int M5 = 19;
int M6 = 4;

void setup() {
  delay(500);
  // Begin Serial
  Serial.begin(115200);
  PS4.begin(targetMAC.c_str());
  Serial.println("Dock Control Default");

  // Servo Setup
  Servo1.attach(M1, 1000, 2000);
  Servo2.attach(M2, 1000, 2000);
  Servo3.attach(M3, 1000, 2000);
  Servo4.attach(M4, 1000, 2000);
  Servo5.attach(M5, 1000, 2000);
  Servo6.attach(M6, 1000, 2000);

  // IRIS Motors
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(26, OUTPUT);


  // Screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.clearDisplay();      // Normal 1:1 pixel scale

  display.setCursor(0, 0);     // Start at top-left corner
  display.print("PS4 Control - ");
  display.setTextSize(2);
  display.print(targetMAC.substring(15,17));
  display.setTextSize(1);
  display.setCursor(0, 24);     // Start at top-left corner
  display.print("Press PS to Connect");

  display.display();

  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcAttachPin(25, ledChannel);
  ledcAttachPin(26, ledChannel2);
  digitalWrite(13,HIGH);
}

void updateScreen(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);     // Start at top-left corner
  display.print("PS4 Control - ");
  display.setTextSize(2);
  display.print(targetMAC.substring(15,17));
  display.setCursor(0,8);
  display.setTextSize(1);
  if(isDock){
    display.print("3-wire");
  }
  else{
    display.print("Iris");
  }
  display.setCursor(0, 24);     // Go to fourth row
  display.setTextSize(1);
  double batteryLevel = 12.5 + PS4.Battery()*12.5;
  if(batteryLevel > 100){
    batteryLevel = 100;
  }
  display.print(batteryLevel,1);
  display.print("% - PS4 Battery");

  display.display();

  /*strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 0, 0));
  strip.show();            // Turn OFF all pixels ASAP*/
}
boolean isFirstLoop = true;
String controlMode = "3-Wire";
int colorState = 0, oldColorState = -1;
long lastScreenUpdate = 0, lastColorUpdate = 0;
void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
      if (isFirstLoop) {
        PS4.setLed(0, 255, 0);
        PS4.sendToController();
        isFirstLoop = false;
        digitalWrite(13,LOW);
        lastScreenUpdate = millis();
        //updateScreen();
      }
      if(millis()-lastScreenUpdate > 2000){
        //if(colorState == 0){
          updateScreen();
        //}
        lastScreenUpdate = millis();
      }
    if (isDock) {
      if (PS4.LStickY() > 5 || PS4.LStickY() < -5) {
        int val = map(PS4.LStickY(), -127, 127, 0, 180);
        Servo1.write(val);
        Serial.print(val);
      }
      else {
        Servo1.write(90);
        Serial.print("90");
      }
      if (PS4.RStickY() > 5 || PS4.RStickY() < -5) {
        int val = map(PS4.RStickY(), -127, 127, 180, 0);
        Servo2.write(val);
        Serial.print(":");
        Serial.print(val);
      }
      else {
        Servo2.write(90);
        Serial.print(":90");
      }
      if (PS4.Right()) {
        Servo3.write(180);
        Serial.print(":180");
      }
      else if (PS4.Left()) {
        Servo3.write(0);
        Serial.print(":0");
      }
      else {
        Servo3.write(90);
        Serial.print(":90");
      }
      if (PS4.Up() || PS4.L1()) {
        Servo4.write(180);
        Serial.print(":180");
      }
      else if (PS4.Down()) {
        Servo4.write(0);
        Serial.print(":0");
      }
      else if (PS4.L2()) {
        int val = map(PS4.L2Value(), -127, 127, 180, 0);
        Servo4.write(val);
        Serial.print(":");
        Serial.print(val);
      }
      else {
        Servo4.write(90);
        Serial.print(":90");
      }
      if (PS4.Square()) {
        Servo5.write(180);
        Serial.print(":180");
      }
      else if (PS4.Circle()) {
        Servo5.write(0);
        Serial.print(":0");
      }
      else {
        Servo5.write(90);
        Serial.print(":90");
      }
      if (PS4.Triangle() || PS4.R1()) {
        Servo6.write(180);
        Serial.print(":180");
      }
      else if (PS4.Cross()) {
        Servo6.write(0);
        Serial.print(":0");
      }
      else if (PS4.R2()) {
        int val = map(PS4.R2Value(), -127, 127, 180, 0);
        Servo6.write(val);
        Serial.print(":");
        Serial.print(val);
      }
      else {
        Servo6.write(90);
        Serial.print(":90");
      }
      Serial.println();

      if (PS4.Touchpad() && millis() - lastColorUpdate > 500) {
        colorState += 1;
        if(colorState == 4){
          colorState = 0;
        }
        lastColorUpdate = millis();
      }

      if (oldColorState != colorState) {
        oldColorState = colorState;
        switch (colorState) {
          case 0:
            PS4.setLed(0, 0, 0);
            break;
          case 1:
            PS4.setLed(255, 0, 0);
            break;
          case 2:
            PS4.setLed(0, 255, 0);
            break;
          case 3:
            PS4.setLed(0, 0, 255);
            break;
        }
        PS4.sendToController();
        delay(5);
      }
      delay(200);
    }
    else {
      if (PS4.LStickY() > 5 || PS4.LStickY() < -5) {
        int leftSpeed = map(PS4.LStickY(), -127, 127, -255, 255);
        Serial.println(PS4.LStickY());
        if (leftSpeed > 0) {
          digitalWrite(12, HIGH);
          digitalWrite(5, LOW);
          ledcWrite(ledChannel, leftSpeed);
        }
        else {
          digitalWrite(12, LOW);
          digitalWrite(5, HIGH);
          ledcWrite(ledChannel, -leftSpeed);
        }
      }
      else{
          digitalWrite(12, LOW);
          digitalWrite(5, HIGH);
          ledcWrite(ledChannel, 0);
      }
      if (PS4.RStickY() > 5 || PS4.RStickY() < -5) {
        int rightSpeed = map(PS4.RStickY(), -127, 127, -255, 255);
        if (rightSpeed < 0) {
          digitalWrite(14, HIGH);
          digitalWrite(2, LOW);
          ledcWrite(ledChannel2, rightSpeed);
        }
        else {
          digitalWrite(14, LOW);
          digitalWrite(2, HIGH);
          ledcWrite(ledChannel2, -rightSpeed);
        }
      }
      else{
          digitalWrite(14, LOW);
          digitalWrite(2, HIGH);
          ledcWrite(ledChannel2, 0);
      }

      if (PS4.Touchpad() && millis() - lastColorUpdate > 500) {
        colorState += 1;
        if(colorState == 4){
          colorState = 0;
        }
        lastColorUpdate = millis();
      }

      if (oldColorState != colorState) {
        oldColorState = colorState;
        switch (colorState) {
          case 0:
            PS4.setLed(0, 0, 0);
            break;
          case 1:
            PS4.setLed(255, 0, 0);
            break;
          case 2:
            PS4.setLed(0, 255, 0);
            break;
          case 3:
            PS4.setLed(0, 0, 255);
            break;
        }
        PS4.sendToController();
        delay(5);
      }
      delay(25);

    }
    // Switch to and from IRIS mode
    if (PS4.Share() && PS4.Options() && millis() - lastUpdate > 2500) {
      lastUpdate = millis();
      isDock = !isDock;
      updateScreen();
      if (isDock) {
        Serial.println("Dock Control");
        Servo1.attach(M1, 1000, 2000);
        Servo2.attach(M2, 1000, 2000);
        Servo3.attach(M3, 1000, 2000);
        Servo4.attach(M4, 1000, 2000);
        Servo5.attach(M5, 1000, 2000);
        Servo6.attach(M6, 1000, 2000);
        PS4.setLed(0, 255, 0);
        PS4.sendToController();
      }
      else {
        Servo1.write(90);
        Servo2.write(90);
        Servo3.write(90);
        Servo4.write(90);
        Servo5.write(90);
        Servo6.write(90);
        Servo1.detach();
        Servo2.detach();
        Servo3.detach();
        Servo4.detach();
        Servo5.detach();
        Servo6.detach();
        Serial.println("IRIS Control");
        PS4.setLed(255, 0, 0);
        PS4.sendToController();
      }
    }
  }
}
