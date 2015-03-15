#pragma once
#include "Arduino.h"
#include "IDebugPort.h"

class Logger
{
public:
	static Logger* Instance();

	static void Create(IDebugPort* pDebugPort); 
	
	void Log(String& pMessage);

	void Log(const char * pMessage);

private:
	Logger(IDebugPort* pDebugPort);
	~Logger(void);
	Logger& operator=(Logger const&);

	static Logger* _logger;

	IDebugPort* _debugPort;
	
};

