// Change the MAC to match that of your PS4 controller
String targetMAC = "aa:bb:cc:dd:ee:01";

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <IRIS.h>
IRIS robot;
HardwareSerial smartMotors(1);
#define motor_right_rear   1
#define motor_right_front   2
#define motor_left_rear   4
#define motor_left_front   3
#define motor_shoulder   5
#define motor_claw   6

// NeoPixels
#include <Adafruit_NeoPixel.h>
#define LED_COUNT 3
#define LED_PIN    6
Adafruit_NeoPixel strip(3, robot.getNeoPin(), NEO_GRB + NEO_KHZ800);

// PS4 Controller
#include <PS4Controller.h>

// How much to increment shoulder and claw position
#define clawIncrement 25
#define shoulderIncrement 25

// Setup the Iris Motor Control
const int freq = 10000;
const int ledChannel = 12;
const int ledChannel2 = 13;
const int resolution = 8;

long lastColorUpdate = 0;
long lastDisplayUpdate = -1;
int clawPositionAverage = 0, currentClawPosition = 0;
int shoulderPositionAverage = 0, currentShoulderPosition = 0;
bool firstFlag = true, isIrisMotors = false;
long clawToggle = 0, shoulderToggle = 0;

/***********************************************************
   Functions
*/
void configurationProcedure();

/***********************************************************
   Main
*/

void setup() {
  // Init LED and turn off
  robot.setLED(false);

  // Start Serial port
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Start the communication line to the motors
  smartMotors.begin(115200, SERIAL_8N1, 16, 17);

  // Countdown on the screen
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.clearDisplay();      // Normal 1:1 pixel scale

  // Neopixels
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Start the PS4 controller Object
  PS4.begin(targetMAC.c_str());// Black

  // Check for Configuration Mode
  if (robot.getButtonState()) {
    configurationProcedure();
  }
  // Setup the on-board motor controllers
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcAttachPin(25, ledChannel);
  ledcAttachPin(26, ledChannel2);

  PS4.setLed(0, 0, 255);
  PS4.sendToController();
  strip.setPixelColor(1, strip.Color(0, 0, 150));
  strip.setPixelColor(2, strip.Color(0, 0, 150));

  strip.show();

}

void screenDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);     // Start at top-left corner
  display.print("PS4 Control - ");
  display.print(targetMAC.substring(15, 17));
  display.setCursor(0, 16);     // Start at second line
  display.print("PushButton : ");
  display.print(robot.getButtonState());
  robot.setLED(robot.getButtonState());
  display.setCursor(0, 24);     // Start at fourth line
  display.print("Light Sensor:");
  display.print(analogRead(34));

  display.display();
}

void loop() {
  if (PS4.isConnected()) {
    if (millis() - lastDisplayUpdate > 250) {
      lastDisplayUpdate = millis();
      screenDisplay();
    }
  }
  else {
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setCursor(0, 0);     // Start at top-left corner
    display.print("PS4 Controller - ");
    display.print(targetMAC.substring(15, 17));
    display.setCursor(0, 16);     // Start at top-left corner
    display.print("Press the PS Button");
    display.setCursor(0, 24);     // Start at top-left corner
    display.print("  to connect");
    display.display();
  }

  if (PS4.isConnected()) {
    if (firstFlag) {
      firstFlag = false;
    }
    if (PS4.Touchpad() && millis() - lastColorUpdate > 500) {
      isIrisMotors = !isIrisMotors;
      lastColorUpdate = millis();
      if (isIrisMotors) {
        PS4.setLed(0, 255, 0);
        PS4.sendToController();
        strip.setPixelColor(1, strip.Color(0, 150, 0));
        strip.setPixelColor(2, strip.Color(0, 150, 0));

        strip.show();
      }
      else {
        PS4.setLed(0, 0, 255);
        PS4.sendToController();
        strip.setPixelColor(1, strip.Color(0, 0, 150));
        strip.setPixelColor(2, strip.Color(0, 0, 150));

        strip.show();
      }
    }

    if (isIrisMotors) { // Control the built-in motors
      if (PS4.LStickY() > 5 || PS4.LStickY() < -5) {
        int leftSpeed = map(PS4.LStickY(), -127, 127, -255, 255);
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
      else {
        digitalWrite(12, LOW);
        digitalWrite(5, HIGH);
        ledcWrite(ledChannel, 0);
      }
      if (PS4.RStickY() > 5 || PS4.RStickY() < -5) {
        int leftSpeed = map(PS4.RStickY(), -127, 127, -255, 255);
        if (leftSpeed < 0) {
          digitalWrite(14, HIGH);
          digitalWrite(2, LOW);
          ledcWrite(ledChannel2, -leftSpeed);
        }
        else {
          digitalWrite(14, LOW);
          digitalWrite(2, HIGH);
          ledcWrite(ledChannel2, leftSpeed);
        }
      }
      else {
        digitalWrite(14, LOW);
        digitalWrite(2, HIGH);
        ledcWrite(ledChannel2, 0);
      }
    }
    else {// Control the Smart Motors
      delay(10);
      int leftSpeed = map(PS4.LStickY(), -127, 127, -99, 99);
      int rightSpeed = map(PS4.RStickY(), -127, 127, 99, -99);
      if (leftSpeed > -10 && leftSpeed < 10) {
        leftSpeed = 0;
      }
      if (rightSpeed > -10 && rightSpeed < 10) {
        rightSpeed = 0;
      }
      robot.SmartMotorSpin(smartMotors, motor_right_rear, rightSpeed);
      robot.SmartMotorSpin(smartMotors, motor_right_front, rightSpeed);
      robot.SmartMotorSpin(smartMotors, motor_left_rear, leftSpeed);
      robot.SmartMotorSpin(smartMotors, motor_left_front, leftSpeed);

      int currentShoulderPosition = robot.SmartMotorReadPosition(smartMotors, motor_shoulder);

      if (currentShoulderPosition != -2048 && currentShoulderPosition != 1621) {
        shoulderPositionAverage = 0.5 * shoulderPositionAverage + 0.5 * currentShoulderPosition;
      }
      if (PS4.Triangle() && millis() - shoulderToggle > 10) {
        shoulderToggle = millis();
        robot.SmartMotorPosition(smartMotors, motor_shoulder, shoulderPositionAverage + shoulderIncrement, 10);
      }
      else if (PS4.Cross() && millis() - shoulderToggle > 10) {
        shoulderToggle = millis();
        robot.SmartMotorPosition(smartMotors, motor_shoulder, shoulderPositionAverage - shoulderIncrement, 10);
      }

      int currentClawPosition = robot.SmartMotorReadPosition(smartMotors, motor_claw);

      if (currentClawPosition != -2048 && currentClawPosition != 1621) {
        clawPositionAverage = 0.5 * clawPositionAverage + 0.5 * currentClawPosition;
      }
      if (PS4.Up() && millis() - clawToggle > 10) {
        clawToggle = millis();
        robot.SmartMotorPosition(smartMotors, motor_claw, clawPositionAverage + clawIncrement, 10);
      }
      else if (PS4.Down() && millis() - clawToggle > 10) {
        clawToggle = millis();
        robot.SmartMotorPosition(smartMotors, motor_claw, clawPositionAverage - clawIncrement, 10);
      }
    }
  }
  else {
    firstFlag = true;
  }
}

void configurationScreen(String lineONE, String lineTWO, String lineTHREE) {
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(0, 0);
  display.print(lineONE);
  display.setCursor(0, 8);
  display.print(lineTWO);
  display.setCursor(0, 16);
  display.print(lineTHREE);
  display.display();
}
void firstProgress() {
  display.setCursor(0, 24);
  for (int i = 0; i < 20; i++) {
    display.print((char)0xDA);
    display.display();
    delay(50);
  }
}

void configurationProcedure() {
  Serial.println("Configuration Mode");
  configurationScreen("Motor Assignment Mode", "Press the Button", "  to begin");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  configurationScreen("Plug in a motor", "Press the Button", "  to assign ID 1");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 1);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 1, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 1, 1000, 500);
  configurationScreen("Plug in a new motor", "Press the Button", " to assign ID 2");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 2);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 2, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 2, 1000, 500);
  configurationScreen("Plug in a new motor", "Press the Button", " to assign ID 3");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 3);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 3, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 3, 1000, 500);
  configurationScreen("Plug in a new motor", "Press the Button", " to assign ID 4");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 4);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 4, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 4, 1000, 500);
  configurationScreen("Plug in a new motor", "Press the Button", " to assign ID 5");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 5);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 5, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 5, 1000, 500);
  configurationScreen("Plug in a new motor", "Press the Button", " to assign ID 6");
  while (robot.getButtonState()) {
    delay(50); // Wait for Button Release
  }
  while (!robot.getButtonState()) {
    delay(100);  // Wait for Button Press
  }
  robot.SmartMotorSetID(smartMotors, 254, 6);
  firstProgress();
  robot.SmartMotorPosition(smartMotors, 6, 500, 500);
  delay(500);
  robot.SmartMotorPosition(smartMotors, 6, 1000, 500);
  configurationScreen("All motors complete", "", "Reset to Begin");
  while (1) {
    delay(100);
  }
}
