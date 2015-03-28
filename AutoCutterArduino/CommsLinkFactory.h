#pragma once
#include "Arduino.h"
#include "CommsLinkBase.h"
#include "SerialComms.h"

typedef enum
{
	COMMS_LINK_SERIAL

}CommsLinkType;

class CommsLinkFactory
{
public:
	CommsLinkBase* GetCommsLink(CommsLinkType pCommsLinkType);	
};

