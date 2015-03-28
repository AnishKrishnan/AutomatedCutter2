#pragma once
#include "Arduino.h"
#include "SerialDebug.h"
#include "IDebugPort.h"

typedef enum
{
	DEBUG_PORT_SERIAL,
	DEBUG_PORT_BLUETOOTH
}DebugPortType;

class DebugPortFactory
{
public:
	static IDebugPort* GetDebugPort(DebugPortType pPortType);
};

