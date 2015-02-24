#pragma once
#include "Logger.h"

static class CommonHelper 
{
public:
	
	template <typename T> static void ConvertValueToCharArray(T pValue, char* pArray, Logger* pLog);
	template <typename T> static T ConvertCharArrayToValue(char* pCharArray, Logger* pLog);

private:

	const static int INT_ARRAY_OFFSET = 3;
};


template <typename T> void CommonHelper::ConvertValueToCharArray(T pValue, char* pArray, Logger* pLog)
{
	if(pLog == NULL)
	{
		throw AutoCutterException("CommonHelper::ConvertFloatToCharArray - pLog is null");
	}

	pLog->Log(std::string("CommonHelper::ConvertFloatToCharArray - Start"));

	if(pArray == NULL)
	{
		throw AutoCutterException("CommonHelper::ConvertFloatToCharArray - pArray is null");
	}

	pLog->Log(std::string("Initialising array and pointer"));
	char* x = (char*)&pValue;

	pLog->Log(std::string("Creating array"));

	for(int i = 0; i < sizeof(T); i++)
	{
		pArray[i] = x[i];
	}

	pLog->Log(std::string("CommonHelper::ConvertFloatToCharArray - Finish"));
}

template <typename T> T CommonHelper::ConvertCharArrayToValue(char* pCharArray, Logger* pLog)
{
	if(pLog == NULL)
	{
		throw AutoCutterException("CommonHelper::ConvertCharArrayToValue - pLog is null");
	}

	pLog->Log(std::string("CommonHelper::ConvertCharArrayToValue - Start"));

	if(pCharArray == NULL)
	{
		throw AutoCutterException("CommonHelper::ConvertCharArrayToValue - pCharArray is null");
	}

	T value;
	char* pointerToValue = (char*)&value;
	for(int i = 0; i < sizeof(T); i++)
	{
		pointerToValue[i] = pCharArray[i];
	}

	pLog->Log(std::string("CommonHelper::ConvertCharArrayToValue - Finish"));

	return value;
}
