#include "GenericBase.h"


HardwareSerial* GenericBase::_debugSerial = NULL;

GenericBase::GenericBase(void)
{
	if(_debugSerial == NULL)
	{
		_debugSerial = &Serial1;
	}

//	Logger::Create(_bluetooth);
//	_log = Logger::Instance();
}


GenericBase::~GenericBase(void)
{
}
