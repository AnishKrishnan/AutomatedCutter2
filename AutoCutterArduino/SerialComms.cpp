#include "SerialComms.h"
#include "Arduino.h"

SerialComms::SerialComms(HardwareSerial& pSerialPort) : CommsLinkBase(), _serialPort(pSerialPort)
{
	_baudRate = SERIALCOMMS_DEFAULT_BAUD;
	_receivedIndex = 0;
	_endStreamCounter = 0;
	_packetStarted = false;
}


SerialComms::SerialComms(HardwareSerial& pSerialPort, int pBaudRate) : _serialPort(pSerialPort)
{
	_baudRate = pBaudRate;
	_receivedIndex = 0;
	_endStreamCounter = 0;
	_packetStarted = false;
}

void SerialComms::OpenConnection()
{

	_serialPort.begin(_baudRate);
	_log->Log("connection openend");

}

void SerialComms::CloseConnection()
{
	_serialPort.flush();
	_serialPort.end();
}

void SerialComms::SendData(Packet& pPacket)
{
	unsigned char rawPacket[PACKET_MAX_RAW_LENGTH];
	unsigned char packetLength = 0;
	
	packetLength = pPacket.ConstructPacket(rawPacket);

	for(unsigned char i = 0; i < packetLength; i++)
	{
		_serialPort.write(rawPacket[i]);
	}
}

void SerialComms::ReceivedByte(unsigned char pByte)
{
	if(!_packetStarted)
	{			
		_log->Log("in received byte");
		if(pByte == PACKET_START_BYTE)
		{		

			_packetStarted = true;
			_receivedData[_receivedIndex++] = pByte;
			_log->Log("packet byte received");
		}
	}
	else
	{
		_receivedData[_receivedIndex++] = pByte;

		if(pByte == PACKET_END_STREAM[_endStreamCounter++])
		{

			if(_endStreamCounter >= PACKET_END_STREAM_LENGTH)
			{
				_log->Log("packet end reached");
				Packet p;
				if(p.TryParseDataToPacket(_receivedData, _receivedIndex))
				{
					_log->Log("firing event");
					//FireReceivedDataEvent(p);
					_listener->RecievedDataCallback(p);
				}
				_endStreamCounter = 0;
				CommonHelper::ClearArray<unsigned char>(_receivedData, _receivedIndex);
				_receivedIndex = 0;
				_packetStarted = false;
			}
		}
		else
		{
			_endStreamCounter = 0;
		}
	}
}

void SerialComms::TempAddListener(ICommsListener* pListener)
{
	if(pListener == NULL)
	{
		_log->Log("Listener is null");
		return;
	}

	_listener = pListener;
}

