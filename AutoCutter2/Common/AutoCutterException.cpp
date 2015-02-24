#include "../stdafx.h"
#include "AutoCutterException.h"


AutoCutterException::AutoCutterException(void)
{
	_message = "An AutoCutterException occurred";
}

AutoCutterException::AutoCutterException(const string& pMessage) : _message(pMessage)
{
	
}

AutoCutterException::AutoCutterException(const char* pMessage) : _message(pMessage)
{

}

string& AutoCutterException::toString()
{
	return _message;
}

AutoCutterException::~AutoCutterException(void)
{
}
