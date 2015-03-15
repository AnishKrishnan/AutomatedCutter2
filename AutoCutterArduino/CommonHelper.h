#pragma once
#include "stdlib.h"
#include "Arduino.h"

class CommonHelper 
{
public:
	
	template <typename T> static void ConvertValueToCharArray(T pValue, unsigned char* pArray);
	template <typename T> static T ConvertCharArrayToValue(unsigned char* pCharArray);

	template <typename T> static void ClearArray(T* pData, int pLength);
private:

	const static int INT_ARRAY_OFFSET = 3;

};


template <typename T> void CommonHelper::ConvertValueToCharArray(T pValue, unsigned char* pArray)
{
	if(pArray != NULL)
	{
		unsigned char* x = (unsigned char*)&pValue;

		for(int i = 0; i < sizeof(T); i++)
		{
			pArray[i] = x[i];
		}
	}
}

template <typename T> T CommonHelper::ConvertCharArrayToValue(unsigned char* pCharArray)
{
	T value;
	if(pCharArray != NULL)
	{	
		char* pointerToValue = (char*)&value;
		for(int i = 0; i < sizeof(T); i++)
		{
			pointerToValue[i] = pCharArray[i];
		}
	}
	return value;
}

template <typename T> void CommonHelper::ClearArray(T* pData, int pLength)
{
	if(pData != NULL)
	{
		for(int i = 0; i < pLength; i++)
		{
			pData[i] = 0;
		}
	}
}
