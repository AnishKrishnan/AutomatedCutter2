#pragma once
#include "Arduino.h"
#include "Config.h"
#include "idebugport.h"
#include "SoftwareSerial\SoftwareSerial.h"

class BluetoothDebug :	public IDebugPort
{
public:
	BluetoothDebug(SoftwareSerial& pSoftwareSerial);
	~BluetoothDebug(void);

	virtual void Setup();
	virtual void Println(String& pMessage);

private:

	SoftwareSerial& _serial;
};

