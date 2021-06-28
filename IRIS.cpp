/*
  IRIS.cpp - Library for interacting with the IRIS Robot.
  Created by Higher Order Innovation, September 3, 2020
  Released into the public domain.
*/

#include "Arduino.h"
#include "IRIS.h"

IRIS::IRIS()
{
	pinMode(_led_pin, OUTPUT);
	pinMode(_push_pin, INPUT_PULLUP);
	
	ledcSetup(ledChannel, freq, resolution);
	ledcAttachPin(_motorA_pwm_pin, ledChannel);
	ledcSetup(ledChannel2, freq, resolution);
	ledcAttachPin(_motorB_pwm_pin, ledChannel2);
	
	pinMode (_motorA_one_pin, OUTPUT);
    pinMode (_motorB_one_pin, OUTPUT);
    pinMode (_motorA_two_pin, OUTPUT);
    pinMode (_motorB_two_pin, OUTPUT);
    pinMode (_motorA_pwm_pin, OUTPUT);
    pinMode (_motorB_pwm_pin, OUTPUT);
    digitalWrite(_motorA_one_pin, LOW);
    digitalWrite(_motorB_one_pin, LOW);
    digitalWrite(_motorA_two_pin, LOW);
    digitalWrite(_motorB_two_pin, LOW);
}

void IRIS::setLED(bool _state)
{
	if(_state){
		digitalWrite(_led_pin, HIGH);
	}
	else{
		digitalWrite(_led_pin, LOW);
	}
}

int IRIS::getLightReading(){
	return analogRead(_light_pin);
}

int IRIS::getNeoPin(){
	return _neo_pin;
}

bool IRIS::getButtonState(){
	return !digitalRead(_push_pin);
}
int IRIS::getButtonPin(){
	return _push_pin;
}

// Set motors from -100 to 100
void IRIS::setMotors(int left, int right){
	right = -right;
	if(left > 0){
		digitalWrite(_motorA_one_pin, LOW);
		digitalWrite(_motorA_two_pin, HIGH);
		ledcWrite(ledChannel, map(left, 100, 0, 255, 0));
	}
	else{
		digitalWrite(_motorA_one_pin, HIGH);
		digitalWrite(_motorA_two_pin, LOW);
		ledcWrite(ledChannel, map(left, -100, 0, 255, 0));
	}
	if(right > 0){
		digitalWrite(_motorB_one_pin, LOW);
		digitalWrite(_motorB_two_pin, HIGH);
		ledcWrite(ledChannel2, map(right, 100, 0, 255, 0));
	}
	else{
		digitalWrite(_motorB_one_pin, HIGH);
		digitalWrite(_motorB_two_pin, LOW);
		ledcWrite(ledChannel2, map(right, -100, 0, 255, 0));
	}
}
