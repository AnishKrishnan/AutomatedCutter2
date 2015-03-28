#pragma once
#include "Arduino.h"
#include "Config.h"
#include "SerialDebug.h"
#include "Logger.h"

class GenericBase
{
protected:
	GenericBase(void);
	~GenericBase(void);

	void Log(String& pMessage);

	void Log(const char* pMessage);

	Logger* _log;

private:

	static IDebugPort* _debugSerial;
};

