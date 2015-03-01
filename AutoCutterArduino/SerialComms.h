#pragma once
#include "HardwareSerial.h"
#include "CommsLinkBase.h"
#include "Packet.h"

#define SERIALCOMMS_DEFAULT_BAUD 9600
class SerialComms : CommsLinkBase
{
public:
	SerialComms(HardwareSerial& pSerialPort);
	SerialComms(HardwareSerial& pSerialPort, int pBaudRate);
	~SerialComms(void);

	virtual void OpenConnection();
	virtual void CloseConnection();
	virtual void SendData(Packet& pPacket);

private:

	void ReceivedByte(char pData);
	
	HardwareSerial _serialPort;
	char _receivedData[PACKET_MAX_RAW_LENGTH];
	char _receivedIndex;

	bool _packetStarted;
	char _endStreamCounter;
	int _baudRate;
};

