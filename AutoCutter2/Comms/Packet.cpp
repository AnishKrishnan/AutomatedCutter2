#include "../stdafx.h"
#include "Packet.h"



Packet::Packet(void)
{
	_log->Log(std::string("Packet::ctor - Start"));

	_data.clear();
	_fullPacketData.clear();
	_totalNumberOfBytes = 0;
	_totalDataBytes = 0;
	_packetType = PACKETTYPE_INVALID;
	_log->Log(std::string("Packet::ctor - Finish"));
}

#pragma region Accessors and Mutators

PacketType Packet::GetPacketType()
{
	return _packetType;
}

void Packet::SetPacketType(PacketType  pPacketType)
{
	if(!IS_VALID_PACKET_TYPE(pPacketType))
	{
		throw AutoCutterException("Packet::SetPacketType - not a valid packet type");
	}

	_packetType = pPacketType;
}

vector<unsigned char>& Packet::GetData()
{
	return _data;
}

void Packet::SetData(vector<unsigned char>& pData)
{
	
	_data = pData;
	_totalDataBytes = pData.size();
}
#pragma endregion

#pragma region Packet Building

uchar_array_t Packet::ConstructPacket()
{
	_log->Log(std::string("Packet::ConstructPacket - Start"));

	_fullPacketData.clear();
	_log->Log(std::string("Creating packet vector from data"));
	_fullPacketData = _data;

	_log->Log(std::string("Adding packet end stream"));
	_fullPacketData.insert(_fullPacketData.end(), PACKET_END_STREAM, PACKET_END_STREAM + PACKET_END_STREAM_LENGTH);

	_log->Log(std::string("Adding packet data size"));
	_fullPacketData.insert(_fullPacketData.begin(), _totalDataBytes);

	_log->Log(std::string("Adding packet type"));
	unsigned char packetTypeByte = (unsigned char)_packetType;
	_fullPacketData.insert(_fullPacketData.begin(), packetTypeByte);

	_log->Log(std::string("Adding total packet size"));
	_totalNumberOfBytes = (unsigned char)_fullPacketData.size();

	_fullPacketData.insert(_fullPacketData.begin(), _totalNumberOfBytes);

	_log->Log(std::string("Adding start byte"));
	_fullPacketData.insert(_fullPacketData.begin(), PACKET_START_BYTE);

	_log->Log(std::string("full packet data size = %i"), _fullPacketData.size());
	_log->Log(std::string("Packet::ConstructPacket - Finish"));

	uchar_array_t data;
	data.data = &(*_fullPacketData.begin());
	data.length = (unsigned char)_fullPacketData.size();
	return data;
}

uchar_array_t Packet::ConstructPacket(vector<unsigned char>& pData)
{
	_log->Log(std::string("Packet::ConstructPacket(vector<unsigned char>& pData) - Start"));

	_log->Log(std::string("Setting packet data"));
	SetData(pData);

	_log->Log(std::string("Constructing packet"));
	uchar_array_t packet = ConstructPacket();
	
	_log->Log(std::string("Packet::ConstructPacket(vector<unsigned char>& pData) - Finish"));

	return packet;
}
#pragma endregion

#pragma region Parsing Raw Data to Packet

bool Packet::TryParseDataToPacket(vector<unsigned char>& pData)
{
	_log->Log(std::string("Packet::TryParseDataToPacket - Start"));
	_log->Log(std::string("pData size = %i"), pData.size());
	int numberOfBytesProcessed = 0, numberOfDataBytes = 0;

	vector<unsigned char>::iterator iterator = pData.begin();
	
	_log->Log(std::string("Parsing start byte"));
	if(*iterator != PACKET_START_BYTE)
	{
		_log->Log(std::string("First byte was not start byte. Will not proceed"));
		return false;
	}
	iterator++;
	_log->Log(std::string("Parsing number of bytes in packet"));
	_totalNumberOfBytes = *iterator;
	if(_totalNumberOfBytes <= 0)
	{
		_log->Log(std::string("Number of bytes is less than or equal to 0"));
		return false;
	}
	iterator++;

	_log->Log(std::string("Parsing packet type"));
	_packetType = static_cast<PacketType>(*iterator);
	if(!IS_VALID_PACKET_TYPE(_packetType))
	{
		_log->Log(std::string("Packet type not part of valid list"));
		return false;
	}
	iterator++;
	numberOfBytesProcessed++;

	_log->Log(std::string("Parsing number of data bytes"));
	_totalDataBytes = *iterator;
	if(_totalDataBytes < 0)
	{
		_log->Log(std::string("Number of data bytes is less than or equal to 0"));
		return false;
	}
	iterator++;
	numberOfBytesProcessed++;
	
	_log->Log(std::string("Parsing data"));
	_data.insert(_data.begin(), iterator, pData.end() - PACKET_END_STREAM_LENGTH + 1);
	numberOfDataBytes = _data.size() - sizeof(_totalDataBytes);
	numberOfBytesProcessed += numberOfDataBytes + PACKET_END_STREAM_LENGTH; 

	_log->Log(std::string("Validating checksums"));
	if(numberOfDataBytes != _totalDataBytes || numberOfBytesProcessed != _totalNumberOfBytes)
	{
		_log->Log(std::string("Checksums are invalid"));
		return false;
	}
	
	_log->Log(std::string("Packet::TryParseDataToPacket - Finish"));
	return true;
}

#pragma endregion
