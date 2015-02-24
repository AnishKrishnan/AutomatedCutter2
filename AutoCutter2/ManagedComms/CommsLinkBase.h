#pragma once

#include "Packet.h"
#include "ICommsListener.h"

public ref class CommsLinkBase
{
public:
	
	CommsLinkBase();

	virtual void OpenConnection() = 0;

	virtual void CloseConnection() = 0;

	virtual void SendData(Packet& pPacket) = 0;

	void AddReceivedDataListener(ICommsListener^ pCommsListener);

protected:
	
	void FireReceivedDataEvent(Packet& p);

	Logger* _log;
private:

	System::Collections::Generic::List<ICommsListener ^> _receivedDataListeners;

};

