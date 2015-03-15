#include "Logger.h"

Logger* Logger::_logger = NULL;

Logger::Logger(IDebugPort* pDebugPort)
{
	if(pDebugPort != NULL)
	{
		_debugPort = pDebugPort;
		_debugPort->Setup();
	}
}

void Logger::Create(IDebugPort* pDebugPort)
{
	if(_logger == NULL)
	{
		_logger = new Logger(pDebugPort);
	}
}

Logger* Logger::Instance()
{
	if(_logger != NULL)
	{
		return _logger;
	}
	else
	{
		return NULL;
	}
}

Logger::~Logger(void)
{
}

void Logger::Log(String& pMessage)
{
#if FULL_TRACE
	
	_debugPort->Println(pMessage);
#endif
}

void Logger::Log(const char * pMessage)
{
	String message = pMessage;

	Log(message);
}