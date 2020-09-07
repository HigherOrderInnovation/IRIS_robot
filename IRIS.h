/*
  IRIS.h - Library for interfacing to the IRIS Robot
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"

class IRIS
{
  public:
    IRIS();
    void setLight();
  private:
    int _ir_pin = 23;
	int _neo_pin = 18;
	int _push_pin = 15;
	int _led_pin = 13;
	int _light_pin = 34;
	int _motorA_one_pin = 12;
	int _motorA_two_pin = 5;
	int _motorA_pwm_pin = 25;
	int _motorB_one_pin = 14;
	int _motorB_two_pin = 2;
	int _motorB_pwm_pin = 26;
};