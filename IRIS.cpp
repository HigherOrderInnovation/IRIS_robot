/*
  IRIS.cpp - Library for interacting with the IRIS Robot.
  Created by Higher Order Innovation, September 3, 2020
  Released into the public domain.
*/

#include "Arduino.h"
#include "IRIS.h"

IRIS::IRIS()
{
}

void IRIS::setLight(bool _state)
{
  digitalWrite(_push_pin, _state);
}