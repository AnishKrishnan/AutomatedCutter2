#include "CommsController.h"
#include "Arduino.h"

CommsController::CommsController(HardwareSerial& pSerial) : _serialPort(pSerial, 115200), _receivedPackets(COMMS_MAX_RECEIVED_PACKETS), _outputPackets(COMMS_MAX_RECEIVED_PACKETS)
{
}

void CommsController::RecievedDataCallback(Packet& pPacket)
{		
	digitalWrite(13, HIGH);
	if(!_receivedPackets.IsFull())
	{
		_receivedPackets.Push(pPacket);
		SendResponse(PACKETTYPE_ACK);
	}
}

void CommsController::RecievedByte(byte pByte)
{

	_serialPort.ReceivedByte(pByte);
}

void CommsController::SendResponse(PacketType pPacketType)
{
	if(IS_VALID_PACKET_TYPE(pPacketType))
	{

		Packet* p = new Packet();
		p->SetPacketType(pPacketType);
		//_outputPackets.Push(*p);
	}
}

void CommsController::ProcessOutbox()
{

	for(byte i = 0; i < _outputPackets.Size(); i++)
	{
		//Packet packetToSend = _outputPackets.Pop();
		//_serialPort.SendData(packetToSend);
	}
}

void CommsController::OpenConnection()
{
	_serialPort.AddReceivedDataListener(*this);
	_serialPort.OpenConnection();
}
