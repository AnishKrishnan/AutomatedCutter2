#include "CommsLinkBase.h"


CommsLinkBase::CommsLinkBase() : GenericBase()
{
}

void CommsLinkBase::AddReceivedDataListener(ICommsListener* pCommsListener)
{
	_receivedDataListeners.push(pCommsListener);
}
void CommsLinkBase::FireReceivedDataEvent(Packet& pPacket)
{
	for(int i = 0; i < _receivedDataListeners.count(); i++)
	{	

		ICommsListener* listener = _receivedDataListeners.pop();

		listener->RecievedDataCallback(pPacket);

		_receivedDataListeners.push(listener);
	}
}