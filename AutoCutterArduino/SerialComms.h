#pragma once
#include "HardwareSerial.h"
#include "CommsLinkBase.h"
#include "Packet.h"

#define SERIALCOMMS_DEFAULT_BAUD 9600
class SerialComms : public CommsLinkBase
{
public:
	SerialComms(HardwareSerial& pSerialPort);
	SerialComms(HardwareSerial& pSerialPort, int pBaudRate);

	virtual void OpenConnection();
	virtual void CloseConnection();
	virtual void SendData(Packet& pPacket);
	void ReceivedByte(byte pData);

private:

	HardwareSerial _serialPort;
	byte _receivedData[PACKET_MAX_RAW_LENGTH];
	byte _receivedIndex;

	bool _packetStarted;
	byte _endStreamCounter;
	int _baudRate;
};

