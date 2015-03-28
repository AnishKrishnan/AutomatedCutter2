#include "SerialDebug.h"


SerialDebug::SerialDebug(HardwareSerial& pHardwareSerial) : _serial(pHardwareSerial)
{
}


SerialDebug::~SerialDebug(void)
{
}

void SerialDebug::Setup(void)
{
	_serial.begin(SERIALCOMMS_DEFAULT_BAUD);
	_serial.println("Debug serial started");
}

void SerialDebug::Println(String& pMessage)
{
	_serial.println(pMessage);
}