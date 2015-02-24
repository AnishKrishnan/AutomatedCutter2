#pragma once
#include "GenericBase.h"
#include "Packet.h"

public ref class ICommsListener
{
public:

	virtual void RecievedDataCallback(Packet& pPacket) = 0;
};

