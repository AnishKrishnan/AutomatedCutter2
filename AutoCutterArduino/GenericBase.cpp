#include "GenericBase.h"


IDebugPort* GenericBase::_debugSerial = NULL;

GenericBase::GenericBase(void)
{
	if(_debugSerial == NULL)
	{
		_debugSerial = new SerialDebug(LOGGER_SERIAL_PORT);
	}

	Logger::Create(_debugSerial);
	_log = Logger::Instance();
}


GenericBase::~GenericBase(void)
{
}
