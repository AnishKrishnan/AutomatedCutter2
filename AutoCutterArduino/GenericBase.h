#pragma once
#include "Arduino.h"
#include "Config.h"
#include "SerialDebug.h"
#include "Logger.h"
#include "DebugPortFactory.h"

class GenericBase
{
protected:
	GenericBase(void);
	~GenericBase(void);

	void LogInfo(String& pMessage);

	void LogInfo(const char* pMessage);

	void LogWarning(String& pMessage);
	void LogWarning(const char* pMessage);

	void LogError(String& pMessage);
	void LogError(const char* pMessage);

	Logger* _log;

private:

	static IDebugPort* _debugSerial;
};

