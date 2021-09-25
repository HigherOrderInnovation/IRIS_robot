/*
  IRIS.h - Library for interfacing to the Iris Robot
*/

#include "Arduino.h"
#include "ESP32_Servo.h"


class IRIS
{
  public:
    	IRIS();
    	void setLED(bool _state);
	int getLightReading();
	int getNeoPin();
	bool getButtonState();
	int getButtonPin();
	void setMotors(int left, int right);
	void setDockMotor(int position, int speed);
	void attachDockMotor(int position);
	void setupMotors();
	void pauseMotors();
	int getIrPin();
	
	//HardwareSerial SerialX(1);
	
	void SmartMotorPosition(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time);
	void SmartMotorStopMove(HardwareSerial &SerialX, uint8_t id);
	void SmartMotorSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID);
	void SmartMotorSetMode(HardwareSerial &SerialX, uint8_t id, uint8_t Mode, int16_t Speed);
	void SmartMotorSpin(HardwareSerial &SerialX, uint8_t id, int16_t Speed);
	void SmartMotorLoad(HardwareSerial &SerialX, uint8_t id);
	void SmartMotorUnload(HardwareSerial &SerialX, uint8_t id);
	int SmartMotorReceiveHandle(HardwareSerial &SerialX, byte *ret);
	int SmartMotorReadPosition(HardwareSerial &SerialX, uint8_t id);
	int SmartMotorReadVin(HardwareSerial &SerialX, uint8_t id);
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
	
	int freq = 5000;
	int ledChannel = 0;
	int ledChannel2 = 1;
	int resolution = 8;

	Servo dock1;
	Servo dock2;
	Servo dock3;
	Servo dock4;
	Servo dock5;
	Servo dock6;

	int dockMotorPin1 = 32;
	int dockMotorPin2 = 33;
	int dockMotorPin3 = 27;
	int dockMotorPin4 = 15;
	int dockMotorPin5 = 19;
	int dockMotorPin6 = 4;

	int dockSensorPin1 = 13;
	int dockSensorPin2 = 35;
	int dockSensorPin3 = 27;
	int dockSensorPin4 = 15;
	int dockSensorPin5 = 19;
	int dockSensorPin6 = 4;
	
	

};
