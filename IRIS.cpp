/*
  IRIS.cpp - Library for interacting with the IRIS Robot.
  Created by Higher Order Innovation, September 3, 2020
  Released into the public domain.
*/

#include "Arduino.h"
#include "IRIS.h"

#ifdef isDocked
#include "ESP32_Servo.h"
#endif

IRIS::IRIS()
{
	pinMode(_led_pin, OUTPUT);
	pinMode(_push_pin, INPUT_PULLUP);
	
	setupMotors();
	
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

void IRIS::setupMotors(){
	ledcSetup(ledChannel, freq, resolution);
	ledcAttachPin(_motorA_pwm_pin, ledChannel);
	ledcSetup(ledChannel2, freq, resolution);
	ledcAttachPin(_motorB_pwm_pin, ledChannel2);
}
void IRIS::pauseMotors(){
	ledcDetachPin(_motorA_pwm_pin);
	ledcDetachPin(_motorB_pwm_pin);
}

void IRIS::attachDockMotor(int position)
{
	switch(position){
		case 1:
			dock1.attach(dockMotorPin1);
			break;	
		case 2:
			dock2.attach(dockMotorPin2);
			break;	
		case 3:
			dock3.attach(dockMotorPin3);
			break;	
		case 4:
			dock4.attach(dockMotorPin4);
			break;	
		case 5:
			dock5.attach(dockMotorPin5);
			break;	
		case 6:
			dock6.attach(dockMotorPin6);
			break;	
	}
}


void IRIS::setDockMotor(int position, int speed){
	int val = map(speed, -100, 100, 0, 180);
	switch(position){
		case 1:
			dock1.write(val);
			break;	
		case 2:
			dock2.write(val);
			break;	
		case 3:
			dock3.write(val);
			break;	
		case 4:
			dock4.write(val);
			break;	
		case 5:
			dock5.write(val);
			break;	
		case 6:
			dock6.write(val);
			break;	
	}
}

////////////////////////////////////////////////////////////////////////////
// Smart Motors

#define GET_LOW_BYTE(A) (uint8_t)((A))
//Macro function  get lower 8 bits of A
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
//Macro function  get higher 8 bits of A
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//put A as higher 8 bits   B as lower 8 bits   which amalgamated into 16 bits integer

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

byte LobotCheckSum(byte buf[]){
  byte i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) {
    temp += buf[i];
  }
  temp = ~temp;
  i = (byte)temp;
  return i;
}

void IRIS::SmartMotorPosition(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time){
  byte buf[10];
  if (position < 0)
    position = 0;
  if (position > 1000)
    position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
  SerialX.write(buf, 10);
}

void IRIS::SmartMotorStopMove(HardwareSerial &SerialX, uint8_t id){
  byte buf[6];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_MOVE_STOP;
  buf[5] = LobotCheckSum(buf);
  SerialX.write(buf, 6);
}

void IRIS::SmartMotorSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID){
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
  SerialX.write(buf, 7);
  
  Serial.println("LOBOT SERVO ID WRITE");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
}

void IRIS::SmartMotorSetMode(HardwareSerial &SerialX, uint8_t id, uint8_t Mode, int16_t Speed){
  byte buf[10];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_OR_MOTOR_MODE_WRITE;
  buf[5] = Mode;
  buf[6] = 0;
  buf[7] = GET_LOW_BYTE((uint16_t)Speed);
  buf[8] = GET_HIGH_BYTE((uint16_t)Speed);
  buf[9] = LobotCheckSum(buf);

  SerialX.write(buf, 10);
}
void IRIS::SmartMotorSpin(HardwareSerial &SerialX, uint8_t id, int16_t Speed){
	int val = map(Speed, -100,100,-1000,1000);
	byte buf[10];

	buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
	buf[2] = id;
	buf[3] = 7;
	buf[4] = LOBOT_SERVO_OR_MOTOR_MODE_WRITE;
	buf[5] = 1;
	buf[6] = 0;
	buf[7] = GET_LOW_BYTE((uint16_t)val);
	buf[8] = GET_HIGH_BYTE((uint16_t)val);
	buf[9] = LobotCheckSum(buf);

	SerialX.write(buf, 10);
}
void IRIS::SmartMotorLoad(HardwareSerial &SerialX, uint8_t id){
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 1;
  buf[6] = LobotCheckSum(buf);

  SerialX.write(buf, 7);
}
void IRIS::SmartMotorUnload(HardwareSerial &SerialX, uint8_t id){
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 0;
  buf[6] = LobotCheckSum(buf);

  SerialX.write(buf, 7);
}
int IRIS::SmartMotorReceiveHandle(HardwareSerial &SerialX, byte *ret){
  bool frameStarted = false;
  bool receiveFinished = false;
  byte frameCount = 0;
  byte dataCount = 0;
  byte dataLength = 2;
  byte rxBuf;
  byte recvBuf[32];
  byte i;

  while (SerialX.available()) {
    rxBuf = SerialX.read();
    delayMicroseconds(100);
    if (!frameStarted) {
      if (rxBuf == LOBOT_SERVO_FRAME_HEADER) {
        frameCount++;
        if (frameCount == 2) {
          frameCount = 0;
          frameStarted = true;
          dataCount = 1;
        }
      }
      else {
        frameStarted = false;
        dataCount = 0;
        frameCount = 0;
      }
    }
    if (frameStarted) {
      recvBuf[dataCount] = (uint8_t)rxBuf;
      if (dataCount == 3) {
        dataLength = recvBuf[dataCount];
        if (dataLength < 3 || dataCount > 7) {
          dataLength = 2;
          frameStarted = false;
        }
      }
      dataCount++;
      if (dataCount == dataLength + 3) {
        if (LobotCheckSum(recvBuf) == recvBuf[dataCount - 1]) {
          frameStarted = false;
          memcpy(ret, recvBuf + 4, dataLength);
          return 1;
        }
        return -1;
      }
    }
  }
}
int IRIS::SmartMotorReadPosition(HardwareSerial &SerialX, uint8_t id){
  int count = 10000;
  int ret;
  byte buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);

  while (SerialX.available())
    SerialX.read();

  SerialX.write(buf, 6);

  while (!SerialX.available()) {
    count -= 1;
    if (count < 0)
      return -2048;
  }

  if (SmartMotorReceiveHandle(SerialX, buf) > 0)
    ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
  else
    ret = -2048;

  return ret;
}
int IRIS::SmartMotorReadVin(HardwareSerial &SerialX, uint8_t id){
  int count = 10000;
  int ret;
  byte buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_VIN_READ;
  buf[5] = LobotCheckSum(buf);

  while (SerialX.available())
    SerialX.read();

  SerialX.write(buf, 6);

  while (!SerialX.available()) {
    count -= 1;
    if (count < 0)
      return -2048;
  }

  if (SmartMotorReceiveHandle(SerialX, buf) > 0)
    ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
  else
    ret = -2049;

  return ret;
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
int IRIS::getIrPin(){
	return _ir_pin;
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
