#pragma once

#include "Packet.h"
#include "QueueList.h"

#include "ICommsListener.h"

#define MAX_COMMS_LISTENERS 255
class CommsLinkBase
{
public:
	
	CommsLinkBase();

	virtual void OpenConnection() = 0;

	virtual void CloseConnection() = 0;

	virtual void SendData(Packet& pPacket) = 0;

	void AddReceivedDataListener(ICommsListener* pCommsListener);

protected:
	
	void FireReceivedDataEvent(Packet& p);

private:

	QueueList<ICommsListener*> _receivedDataListeners;

};

