#pragma once
#include "HardwareSerial.h"
#include "Packet.h"
#include "SerialComms.h"
#include "ICommsListener.h"
#include "CommsLinkBase.h"
#include "QueueList.h" 

#define COMMS_MAX_RECEIVED_PACKETS 255
class CommsController : ICommsListener
{
public:
	CommsController(HardwareSerial& pSerial);
	void RecievedByte(unsigned char pByte);
	void RecievedDataCallback(Packet& pPacket);
	void OpenConnection();
	void ProcessOutbox();

private:
	void SendResponse(PacketType pPacketType);
	SerialComms _serialPort;

	QueueList<Packet> _receivedPackets;
	QueueList<Packet> _outputPackets;
};

