#pragma once

#include "CommsLinkBase.h"
#include "SerialCommsLink.h"
#include "GenericBase.h"
#include "ICommsListener.h"
#include "CustomPoint3d.h"
#include "Packet.h"
#include "GenericWrapper.h"

public ref class CommsController : ICommsListener
{

#pragma region Public Methods

public:
	CommsController();

	void ConnectToDevice(System::String^ pPortName);

	virtual void RecievedDataCallback(Packet& pPacket) override;

	void AddCoordinate(CustomPoint3d<float>& pStartPoint, CustomPoint3d<float>& pEndPoint);

	void AddLine(vector<CustomPoint3d<float>>& pLine);

	void SendPacket(Packet& pPacket);

	void SendAllPackets();

#pragma endregion

private: 
#pragma region Private Methods

	vector<char> ConvertPointToData(CustomPoint3d<float>& pPoint);

	static void PacketAckTimerElapsed(System::Object^  sender, System::Timers::ElapsedEventArgs^  e);

#pragma endregion

#pragma region Private Members

	CommsLinkBase^ _commsLink;
	Logger* _log;
	ConfigurationManager* _configManager;
	System::Collections::Generic::List<GenericWrapper<Packet> ^> _packetsToSend;
	System::Timers::Timer _packetAckTimer;
	bool _ackReceived;

#pragma endregion
};

