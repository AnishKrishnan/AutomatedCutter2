#pragma once
#include "Logger.h"
#include "ConfigurationManager.h"
class GenericBase
{
public:


protected:
	GenericBase(void);
	~GenericBase(void);
	Logger* _log;
	ConfigurationManager* _config;
	
};

