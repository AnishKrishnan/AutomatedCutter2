#include "CommsController.h"
#include "Arduino.h"

CommsController::CommsController(HardwareSerial& pSerial) : _serialPort(pSerial)
{
}

void CommsController::RecievedDataCallback(Packet& pPacket)
{		
	_receivedPackets.push(pPacket);
	SendResponse(PACKETTYPE_ACK);
}

void CommsController::RecievedByte(unsigned char pByte)
{

	_serialPort.ReceivedByte(pByte);
}

void CommsController::SendResponse(PacketType pPacketType)
{
	if(IS_VALID_PACKET_TYPE(pPacketType))
	{
		Packet* p = new Packet();
		p->SetPacketType(pPacketType);
		_outputPackets.push(*p);	
	}
}

void CommsController::ProcessOutbox()
{
	
	for(unsigned char i = 0; i < _outputPackets.count(); i++)
	{
		digitalWrite(13, HIGH);
		Packet packetToSend = _outputPackets.pop();
		_serialPort.SendData(packetToSend);
	}
}

void CommsController::OpenConnection()
{
	_serialPort.AddReceivedDataListener(this);
	_serialPort.TempAddListener(this);
	_serialPort.OpenConnection();
}
