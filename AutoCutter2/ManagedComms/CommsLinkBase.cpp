#include "../stdafx.h"
#include "CommsLinkBase.h"


CommsLinkBase::CommsLinkBase()
{
	_log = Logger::instance();
	if(_log == NULL)
	{
		throw AutoCutterException("CommsLinkBase::ctor - could not retrieve log instance");
	}
}

void CommsLinkBase::AddReceivedDataListener(ICommsListener^ pCommsListener)
{
	_log->Log(std::string("CommsLinkBase::AddReceivedDataListener - Start"));
	if(pCommsListener == nullptr)
	{
		throw AutoCutterException("CommsLinkBase::AddReceivedDataListener - pCommsListener is null");
	}

	_log->Log(std::string("Adding pCommsListener to list"));

	_receivedDataListeners.Add(pCommsListener);

	_log->Log(std::string("CommsLinkBase::AddReceivedDataListener - Finish"));
}
void CommsLinkBase::FireReceivedDataEvent(Packet& pPacket)
{
	_log->Log(std::string("CommsLinkBase::FireReceivedDataEvent - Start"));

	_log->Log(std::string("Firing received data event on %i listeners"), _receivedDataListeners.Count);

	for(int i = 0; i < _receivedDataListeners.Count; i++)
	{
		_receivedDataListeners[i]->RecievedDataCallback(pPacket);
	}

	_log->Log(std::string("CommsLinkBase::FireReceivedDataEvent - Finish"));
}