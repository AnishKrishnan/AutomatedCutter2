#include "../stdafx.h"
#include "SerialCommsLink.h"

#define DEFAULT_BAUD_RATE		9600

SerialCommsLink::SerialCommsLink(System::String^ pPortName, int pBaudRate) : CommsLinkBase()
{
	Construct(pPortName, pBaudRate);
}

SerialCommsLink::SerialCommsLink(System::String^ pPortName) : CommsLinkBase()
{
	Construct(pPortName, DEFAULT_BAUD_RATE);
}

void SerialCommsLink::OpenConnection()
{
	_log->Log(std::string("SerialCommsLink::OpenConnection - Start"));

	_log->Log(std::string("Opening connection"));
	
	if(!_serialPort->IsOpen)
	{
		_serialPort->Open();
	}
	
	_log->Log(std::string("SerialCommsLink::OpenConnection - Finish"));
}

void SerialCommsLink::SendData(Packet& pPacket)
{
	_log->Log(std::string("SerialCommsLink::SendData - Start"));

	_log->Log(std::string("Constructing packet"));
	char * data = pPacket.ConstructPacket();

	if(data == NULL)
	{
		throw AutoCutterException("Could not construct packet");
	}

	_log->Log(std::string("Sending data"));
	System::String^ outputString = gcnew System::String(data);
	
	_serialPort->Write(outputString);

	delete outputString;

	_log->Log(std::string("SerialCommsLink::SendData - Finish"));
}

void SerialCommsLink::CloseConnection()
{
	_log->Log(std::string("SerialCommsLink::CloseConnection - Start"));

	_log->Log(std::string("Closing serial port"));

	if(_serialPort->IsOpen)
	{
		_serialPort->Close();
	}

	_log->Log(std::string("SerialCommsLink::CloseConnection - Finish"));
}

void SerialCommsLink::ReceiveByte(char pByte)
{
	_log->Log(std::string("SerialCommsLink::ReceiveByte - Start"));

	
	if(!_packetStarted)
	{
		_log->Log(std::string("Checking for start byte"));
		if(pByte == PACKET_START_BYTE)
		{
			_log->Log(std::string("Start byte recieved"));
			_packetStarted = true;
			_receivedData->GetInternal()->push_back(pByte);
		}
	}
	else
	{
		_log->Log(std::string("Pusing byte to list"));
		_receivedData->GetInternal()->push_back(pByte);

		if(pByte == PACKET_END_STREAM[_endStreamCounter++])
		{
			_log->Log(std::string("end stream byte received"));
			if(_endStreamCounter >= PACKET_END_STREAM_LENGTH)
			{
				_log->Log(std::string("Parsing packet"));
				Packet p;
				if(p.TryParseDataToPacket(*(_receivedData->GetInternal())))
				{
					_log->Log(std::string("packet parsed. Firing data received event"));
					FireReceivedDataEvent(p);
				}
				else
				{
					throw AutoCutterException("Could not successfully parse data");
				}
				_log->Log(std::string("resetting packet"));
				_endStreamCounter = 0;
				_receivedData->GetInternal()->clear();
				_packetStarted = false;
			}
		}
		else
		{
			_log->Log(std::string("byte was not end stream. resetting end stream counter"));
			_endStreamCounter = 0;
		}

	}

	_log->Log(std::string("SerialCommsLink::ReceiveByte - Finish"));
}

void SerialCommsLink::Construct(System::String^ pPortName, int pBaudRate)
{
	_log->Log(std::string("SerialCommsLink::ctor - Start"));

	if(pPortName == nullptr)
	{
		throw AutoCutterException("SerialCommsLink::ctor - pPortName is null");
	}
	_serialPort = gcnew System::IO::Ports::SerialPort(pPortName, pBaudRate);

	_receivedData = gcnew GenericWrapper<vector<char>>(new vector<char>());

	_serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &SerialCommsLink::DataReceivedEventHandler);
}

void SerialCommsLink::DataReceivedEventHandler(System::Object^  pSender, System::IO::Ports::SerialDataReceivedEventArgs^  pEArgs)
{
	while(_serialPort->BytesToRead)
	{
		this->ReceiveByte(_serialPort->ReadByte());
	}
}

