// IRIS Button Testing Step 2
// An interrupt is used to trigger the buttonPress

#include <IRIS.h>
IRIS robot;

int buttonChangeCounter = 0;
bool isButtonChanged = false;
long lastButtonChangeTime = 0;
void setup() {
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(115200);
  Serial.println("Button Interrupt Test");

  attachInterrupt(digitalPinToInterrupt(robot.getButtonPin()), button_state_change, FALLING);

}

void button_state_change() {
  isButtonChanged = true;
}

void loop() {
  if (isButtonChanged) {
    isButtonChanged = false;
    Serial.println("TESTING");
    if(millis()-lastButtonChangeTime > 200){
      Serial.println("Button State Changed");
      lastButtonChangeTime = millis();
    }
  }
  delay(50);
}
