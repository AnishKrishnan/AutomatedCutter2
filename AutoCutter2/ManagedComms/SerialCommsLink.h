#pragma once
#include "CommsLinkBase.h"
#include "ICommsListener.h"
#include "GenericWrapper.h"

public ref class SerialCommsLink : CommsLinkBase
{

public:
#pragma region Constructor Definitions
	SerialCommsLink(System::String^ pPortName);
	SerialCommsLink(System::String^ pPortName, int pBaudRate);

#pragma endregion

#pragma region Override Methods

	virtual void OpenConnection() override;

	virtual void CloseConnection() override;

	virtual void SendData(Packet& pPacket) override;

#pragma endregion

private:

#pragma region Private Methods

	void ReceiveByte(char data);

	void Construct(System::String^ pPortName, int pBaudRate);

	void SerialCommsLink::DataReceivedEventHandler(System::Object^  pSender, System::IO::Ports::SerialDataReceivedEventArgs^  pEArgs);

#pragma endregion

#pragma region Private Members

	System::IO::Ports::SerialPort^ _serialPort;	

	GenericWrapper<vector<char>>^ _receivedData;

	bool _packetStarted;

	int _endStreamCounter;

#pragma endregion
	
};

