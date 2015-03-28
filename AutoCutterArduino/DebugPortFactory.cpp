#include "DebugPortFactory.h"

IDebugPort* DebugPortFactory::GetDebugPort(DebugPortType pPortType)
{
	IDebugPort* debugPort = NULL;
	switch(pPortType)
	{
		case DEBUG_PORT_SERIAL:
			debugPort = new SerialDebug(LOGGER_SERIAL_PORT);
			break;
		default:
			break;
	}

	return debugPort;
}