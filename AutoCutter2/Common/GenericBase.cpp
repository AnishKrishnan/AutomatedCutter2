#include "../stdafx.h"
#include "GenericBase.h"


GenericBase::GenericBase(void)
{
	_config = ConfigurationManager::instance();
	if(!_config)
	{
		throw AutoCutterException("Could not find configuration manager");
	}

	string logPath = _config->getValue("LogPath");
	if(logPath.empty())
	{
		throw AutoCutterException("Please specify a value for LogPath in the config file");
	}
	string trace = _config->getValue("Trace");
	bool traceOn = false;
	if(trace.empty() || trace.compare("True") == 0)
	{
		traceOn = true;
	}

	Logger::create(logPath, traceOn);
	_log = Logger::instance();

}

GenericBase::~GenericBase(void)
{
}
