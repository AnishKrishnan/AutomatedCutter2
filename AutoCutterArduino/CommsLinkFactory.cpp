#include "CommsLinkFactory.h"

CommsLinkBase* CommsLinkFactory::GetCommsLink(CommsLinkType pCommsLinkType)
{
	CommsLinkBase* commsLink = NULL;

	switch(pCommsLinkType)
	{
		case COMMS_LINK_SERIAL:
			commsLink = new SerialComms(SERIAL_COMMS_LINK_PORT);
			break;
		default:
			break;
	}

	return commsLink;
}