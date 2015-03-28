#pragma once
#include "HardwareSerial.h"
#include "CommsLinkBase.h"
#include "Packet.h"
#include "Config.h"

class SerialComms : public CommsLinkBase
{
public:
	SerialComms(HardwareSerial& pSerialPort);
	SerialComms(HardwareSerial& pSerialPort, int pBaudRate);

	virtual void OpenConnection();
	virtual void CloseConnection();
	virtual void SendData(Packet& pPacket);
	void ReceivedByte(unsigned char pData);

	void TempAddListener(ICommsListener* pListener);

private:

	HardwareSerial _serialPort;
	unsigned char _receivedData[PACKET_MAX_RAW_LENGTH];
	unsigned char _receivedIndex;

	bool _packetStarted;
	unsigned char _endStreamCounter;
	int _baudRate;

	ICommsListener* _listener;
};

