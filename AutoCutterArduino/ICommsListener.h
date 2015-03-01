#pragma once
#include "Packet.h"

class ICommsListener
{
public:

	virtual void RecievedDataCallback(Packet& pPacket) = 0;
};

