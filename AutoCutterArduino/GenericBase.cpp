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

void GenericBase::Log(String& pMessage)
{
	_log->Log(pMessage);
}

void GenericBase::Log(const char* pMessage)
{
	_log->Log(pMessage);
}