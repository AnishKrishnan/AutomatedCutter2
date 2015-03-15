#pragma once
#include "Config.h"
#include "BluetoothDebug.h"
#include "Logger.h"
class GenericBase
{
protected:
	GenericBase(void);
	~GenericBase(void);

	Logger* _log;

private:

	static SoftwareSerial* _bluetoothSerial;
	static BluetoothDebug* _bluetooth;
};

