#pragma once
#include "Arduino.h"
#include "IDebugPort.h"
#include "Config.h"

typedef enum
{
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
}LogLevel;

class Logger
{
public:
	static Logger* Instance();

	static void Create(IDebugPort* pDebugPort); 
	
	void Log(LogLevel pLogLevel, String& pMessage);

	void Log(LogLevel pLogLevel, const char * pMessage);

private:
	Logger(IDebugPort* pDebugPort);
	~Logger(void);
	Logger& operator=(Logger const&);

	static Logger* _logger;

	IDebugPort* _debugPort;
	
};

