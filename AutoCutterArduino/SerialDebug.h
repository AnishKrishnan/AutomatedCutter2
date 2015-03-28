#pragma once
#include "Arduino.h"
#include "Config.h"
#include "IDebugPort.h"
#include "HardwareSerial.h"

class SerialDebug : public IDebugPort
{
public:
	SerialDebug(HardwareSerial& pHardwareSerial);
	~SerialDebug(void);

	virtual void Setup();
	virtual void Println(String& pMessage);

private:

	HardwareSerial& _serial;
};

