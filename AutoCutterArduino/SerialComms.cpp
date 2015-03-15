#include "SerialComms.h"
#include "Arduino.h"

SerialComms::SerialComms(HardwareSerial& pSerialPort) : _serialPort(pSerialPort)
{
	_baudRate = SERIALCOMMS_DEFAULT_BAUD;
	_receivedIndex = 0;
	_endStreamCounter = 0;
}


SerialComms::SerialComms(HardwareSerial& pSerialPort, int pBaudRate) : _serialPort(pSerialPort)
{
	_baudRate = pBaudRate;
	_receivedIndex = 0;
	_endStreamCounter = 0;
}

void SerialComms::OpenConnection()
{

	_serialPort.begin(_baudRate);

}

void SerialComms::CloseConnection()
{
	_serialPort.flush();
	_serialPort.end();
}

void SerialComms::SendData(Packet& pPacket)
{
	byte rawPacket[PACKET_MAX_RAW_LENGTH];
	byte packetLength = 0;
	
	packetLength = pPacket.ConstructPacket(rawPacket);

	for(byte i = 0; i < packetLength; i++)
	{
		_serialPort.print(rawPacket[i]);
	}
}

void SerialComms::ReceivedByte(byte pByte)
{

	if(!_packetStarted)
	{			

		if(pByte == PACKET_START_BYTE)
		{		
			_packetStarted = true;
			_receivedData[_receivedIndex++] = pByte;

		}
	}
	else
	{
		_receivedData[_receivedIndex++] = pByte;

		if(pByte == PACKET_END_STREAM[_endStreamCounter++])
		{

			if(_endStreamCounter >= PACKET_END_STREAM_LENGTH)
			{
				Packet p;
				if(p.TryParseDataToPacket(_receivedData, _receivedIndex))
				{
					FireReceivedDataEvent(p);
				}
				_endStreamCounter = 0;
				CommonHelper::ClearArray<byte>(_receivedData, _receivedIndex);
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


