#include "../stdafx.h"
#include "Logger.h"

const string Logger::LOGFILE_PREFIX = "Log_";
const string Logger::LOGFILE_SUFFIX = ".txt";
Logger* Logger::_logger = NULL;

Logger::Logger(string& pFilePath, bool pTrace)
{
	_fullTrace = pTrace;
	time_t t = time(0);
	struct tm * now = localtime(&t);
	stringstream filePathBuilder;
	filePathBuilder << pFilePath << LOGFILE_PREFIX << now->tm_year << "_" << now->tm_mon << "_" << now->tm_mday << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << LOGFILE_SUFFIX;

	_logFile = ofstream(filePathBuilder.str());

	if(!_logFile.is_open())
	{
		throw AutoCutterException("Could not open log file");
	}
}


void Logger::create(string& pFilePath, bool pTrace)
{
	if(!_logger)
	{
		_logger = new Logger(pFilePath, pTrace);
	}

}

Logger* Logger::instance()
{
	if(_logger)
	{
		return _logger;
	}else
	{
		throw AutoCutterException("Please instantiate logger using the create() function");
	}

}

Logger::~Logger(void)
{
	_logFile.flush();
	_logFile.close();
}

void Logger::Log(string& pMessage, ...)
{
	if(_fullTrace)
	{
		char message[MAX_LOGSIZE];

		va_list args;
		va_start(args, pMessage);

		int charCount = vsprintf(message, pMessage.c_str(), args);
		if(charCount > 0)
		{
			_logFile << message << endl;
			va_end(args);
		}
	}
}

void Logger::LogError(string& pMessage, ...)
{
		char message[MAX_LOGSIZE];

		va_list args;
		va_start(args, pMessage);

		int charCount = vsprintf(message, pMessage.c_str(), args);
		if(charCount > 0)
		{
			_logFile << message << endl;
			va_end(args);
		}

}
