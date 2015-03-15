#include "CommsLinkBase.h"


CommsLinkBase::CommsLinkBase() : _receivedDataListeners(MAX_COMMS_LISTENERS)
{
}

void CommsLinkBase::AddReceivedDataListener(ICommsListener* pCommsListener)
{
	_receivedDataListeners.Push(pCommsListener);
}
void CommsLinkBase::FireReceivedDataEvent(Packet& pPacket)
{
	for(int i = 0; i < _receivedDataListeners.Size(); i++)
	{	

		ICommsListener* listener = _receivedDataListeners.Pop();

		listener->RecievedDataCallback(pPacket);

		_receivedDataListeners.Push(listener);
	}
}