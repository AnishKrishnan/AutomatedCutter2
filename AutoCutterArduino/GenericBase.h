#pragma once
#include "Config.h"
#include "SerialDebug.h"
#include "Logger.h"

class GenericBase
{
protected:
	GenericBase(void);
	~GenericBase(void);

	Logger* _log;

private:

	static IDebugPort* _debugSerial;
};

