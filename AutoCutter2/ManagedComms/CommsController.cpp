#include "../stdafx.h"
#include "CommsController.h"


CommsController::CommsController()
{
	_log = Logger::instance();
	_configManager = ConfigurationManager::instance();

	if(_log == NULL)
	{
		throw AutoCutterException("CommsController::ctor - pLog is null");
	}

	if(_configManager == NULL)
	{
		throw AutoCutterException("CommsController::ctor - pConfigManager is null");
	}

	_packetsToSend.Clear();

	_packetAckTimer.Elapsed += gcnew System::Timers::ElapsedEventHandler(CommsController::PacketAckTimerElapsed);
	_packetAckTimer.Interval = atof(_configManager->getValue("PacketAckTimeout").c_str());
}

void CommsController::ConnectToDevice(System::String^ pPortName)
{
	_log->Log(std::string("CommsController::ConnectToDevice - Start"));
	if(pPortName == nullptr)
	{
		throw AutoCutterException("CommsController::ctor - pPortName is null");
	}

	_log->Log(std::string("Instantiating comms link"));
	_commsLink = gcnew SerialCommsLink(pPortName);
	_commsLink->AddReceivedDataListener(this);

	_log->Log(std::string("Opening connection"));
	_commsLink->OpenConnection();

	_log->Log(std::string("CommsController::ConnectToDevice - Finish"));
}

void CommsController::AddCoordinate(CustomPoint3d<float>& pStartPoint, CustomPoint3d<float>& pEndPoint)
{
	_log->Log(std::string("CommsController::AddCoordinate - Start"));
	Packet* packetToAdd = new Packet();
	packetToAdd->SetPacketType(PACKETTYPE_PATH_REQUEST);

	vector<char> packetData;

	_log->Log(std::string("Adding start point to packet data"));
	vector<char> startPointData = ConvertPointToData(pStartPoint);
	packetData.insert(packetData.end(), startPointData.begin(), startPointData.end());

	_log->Log(std::string("Adding end point to packet data"));
	vector<char> endPointData = ConvertPointToData(pEndPoint);
	packetData.insert(packetData.end(), endPointData.begin(), endPointData.end());

	packetToAdd->SetData(packetData);

	_log->Log(std::string("Adding packet to list"));
	GenericWrapper<Packet> ^ packetWrapper = gcnew GenericWrapper<Packet>(packetToAdd);
	_packetsToSend.Add(packetWrapper);

	_log->Log(std::string("CommsController::AddCoordinate - Finish"));
}

void CommsController::AddLine(vector<CustomPoint3d<float>>& pLine)
{
	_log->Log(std::string("CommsController::AddLine - Start"));

	_log->Log(std::string("Adding points in line to list of packets to send"));

	//Start from the second point in the line to create the displacement
	for(int i = 1; i < pLine.size(); i++)
	{
		AddCoordinate(pLine.at(i-1), pLine.at(i));
	}

	_log->Log(std::string("CommsController::AddLine - Finish"));
}

void CommsController::RecievedDataCallback(Packet& pPacket)
{
	_log->Log(std::string("CommsController::ReceivedDataCallback - Start"));
	
	switch(pPacket.GetPacketType())
	{
		case PACKETTYPE_ACK:
			_ackReceived = true;
			break;

		default:
			break;
	}

	_log->Log(std::string("CommsController::ReceivedDataCallback - Finish"));
}

vector<char> CommsController::ConvertPointToData(CustomPoint3d<float>& pPoint)
{
	_log->Log(std::string("CommsController::ConvertPointToData - Start"));
	vector<char> convertedData;
	char floatData[sizeof(float)];

	_log->Log(std::string("Converting x coordinate"));
	CommonHelper::ConvertValueToCharArray<float>(pPoint.GetX(), floatData, _log);
	convertedData.insert(convertedData.end(), floatData, floatData + sizeof(float));

	_log->Log(std::string("Converting y coordinate"));
	CommonHelper::ConvertValueToCharArray<float>(pPoint.GetY(), floatData, _log);
	convertedData.insert(convertedData.end(), floatData, floatData + sizeof(float));

	_log->Log(std::string("Converting z coordinate"));
	CommonHelper::ConvertValueToCharArray<float>(pPoint.GetZ(), floatData, _log);
	convertedData.insert(convertedData.end(), floatData, floatData + sizeof(float));

	_log->Log(std::string("CommsController::ConvertPointToData - Finish"));
	return convertedData;
}

void CommsController::SendPacket(Packet& pPacket)
{
	_log->Log(std::string("CommsController::SendPacket - Start"));

	_ackReceived = false;
	_commsLink->SendData(pPacket);
	_packetAckTimer.Start();

	//hold until ack received or timeout
	while(!_ackReceived)
	{
	}

	_ackReceived = false;
	_packetAckTimer.Stop();
	
	_log->Log(std::string("CommsController::SendPacket - Finish"));
}

void CommsController::SendAllPackets()
{
	_log->Log(std::string("CommsController::SendAllPackets - Start"));

	_log->Log(std::string("Sending packets"));

	for(int i = 0; i < _packetsToSend.Count; i++)
	{

	}

	_log->Log(std::string("CommsController::SendAllPackets - End"));
}

void CommsController::PacketAckTimerElapsed(System::Object^ pSource, System::Timers::ElapsedEventArgs^ pEArgs)
{
	throw AutoCutterException("Did not receive packet in the appropriate amount of time");
}