#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdarg.h>
#include <ctime>
#include "AutoCutterException.h"

using namespace std;
class Logger
{

public:
	static Logger* instance();
	static void create(string& pFilePath, bool pTrace);


	void Log(string& pMessage, ...);

	void LogError(string& pMessage, ...);

	void writeLog();
	~Logger(void);

private:
	string _filePath;
	bool _fullTrace;
	ofstream _logFile;
	stringstream _stringBuilder;
	static const int MAX_LOGSIZE = 1000;

	static const string LOGFILE_PREFIX;
	static const string LOGFILE_SUFFIX;

	static Logger* _logger;

	Logger(string& pFilePath, bool pTrace);
	Logger(void);
	Logger& operator=(Logger const&);
};

