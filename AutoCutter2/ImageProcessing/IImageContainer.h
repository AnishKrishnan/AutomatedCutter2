#pragma once
#ifdef IMAGEPROCESSING_EXPORTS
#define IMAGEPROCESSING_API __declspec(dllexport)
#else
#define IMAGEPROCESSING_API __declspec(dllimport)
#endif
#include "GenericBase.h"

class IImageContainer
{
public:

	virtual ~IImageContainer(void){};

	virtual int GetWidth() = 0;

	virtual int GetHeight() = 0;

	virtual int* GetData() = 0;

	virtual int GetStep() = 0;
};

