#pragma once
#include "HardwareSerial.h"

class CommsController
{
public:
	CommsController(HardwareSerial& pSerial);
	~CommsController(void);

private:

	HardwareSerial _serial;

};

