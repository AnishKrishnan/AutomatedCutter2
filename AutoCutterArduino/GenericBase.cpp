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

void GenericBase::LogInfo(String& pMessage)
{
	_log->Log(LOG_LEVEL_INFO,pMessage);
}

void GenericBase::LogInfo(const char* pMessage)
{
	_log->Log(LOG_LEVEL_INFO,pMessage);
}

void GenericBase::LogWarning(String& pMessage)
{
	_log->Log(LOG_LEVEL_WARNING,pMessage);
}

void GenericBase::LogWarning(const char* pMessage)
{
	_log->Log(LOG_LEVEL_WARNING,pMessage);
}

void GenericBase::LogError(String& pMessage)
{
	_log->Log(LOG_LEVEL_ERROR,pMessage);
}

void GenericBase::LogError(const char* pMessage)
{
	_log->Log(LOG_LEVEL_ERROR,pMessage);
}