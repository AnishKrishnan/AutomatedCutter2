#include "SerialDebug.h"


SerialDebug::SerialDebug(HardwareSerial& pHardwareSerial) : _serial(pHardwareSerial)
{
}


SerialDebug::~SerialDebug(void)
{
}

void SerialDebug::Setup(void)
{
	_serial.begin(SERIALDEBUG_BAUD);
}

void SerialDebug::Println(String& pMessage)
{
	_serial.println(pMessage);
}