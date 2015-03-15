#include "Packet.h"

Packet::Packet(void)
{
	CommonHelper::ClearArray<byte>(_data, PACKET_MAX_DATA_LENGTH);
	_totalNumberOfBytes = 0;
	_totalDataBytes = 0;
	_packetType = PACKETTYPE_INVALID;
}

#pragma region Accessors and Mutators

PacketType Packet::GetPacketType()
{
	return _packetType;
}

void Packet::SetPacketType(PacketType  pPacketType)
{
	if(IS_VALID_PACKET_TYPE(pPacketType))
	{
		_packetType = pPacketType;
	}
}

void Packet::GetData(byte* pData)
{
	if(pData != NULL)
	{
		for(byte i = 0; i < _totalDataBytes; i++)
		{
			pData[i] = _data[i]; 
		}
	}

}

void Packet::SetData(byte * pData, byte pLength)
{
	if(pData != NULL && pLength < PACKET_MAX_DATA_LENGTH)
	{
		for(byte i = 0; i < pLength; i++)
		{
			_data[i] = pData[i];
		}
		_totalDataBytes = pLength;
	}
	
}
#pragma endregion

#pragma region Packet Building

byte Packet::ConstructPacket(byte * pRawPacket)
{
	byte index = 0;
	if(pRawPacket != NULL)
	{
		//Adding start byte
		pRawPacket[index++] = PACKET_START_BYTE;

		//total lenght = packet type + dataLength + data + end stream
		_totalNumberOfBytes = sizeof(char) + sizeof(_totalDataBytes) + _totalDataBytes + PACKET_END_STREAM_LENGTH;
		pRawPacket[index++] = _totalNumberOfBytes;

		pRawPacket[index++] = (char)_packetType;

		pRawPacket[index++] = _totalDataBytes;

		for(byte i = 0; i < _totalDataBytes; i++)
		{
			pRawPacket[index++] = _data[i];
		}

		for(byte i = 0; i < PACKET_END_STREAM_LENGTH; i++)
		{
			pRawPacket[index++] = PACKET_END_STREAM[i];
		}
	}

	return index;

}

byte Packet::ConstructPacket(byte * pRawPacket, byte * pData, byte pLength)
{
	SetData(pData, pLength);

	byte packetLength = ConstructPacket(pRawPacket);

	return packetLength;
}
#pragma endregion

#pragma region Parsing Raw Data to Packet

bool Packet::TryParseDataToPacket(byte * pData, byte pLength)
{
	if(pData != NULL && pLength < PACKET_MAX_RAW_LENGTH)
	{

		int numberOfBytesProcessed = 0, numberOfDataBytes = 0;

		byte index = 0;	

		if(pData[index] != PACKET_START_BYTE)
		{
			return false;
		}
		index++;
		
		_totalNumberOfBytes = pData[index];
		if(_totalNumberOfBytes <= 0)
		{
			return false;
		}
		index++;

		_packetType = static_cast<PacketType>(pData[index]);
		if(!IS_VALID_PACKET_TYPE(_packetType))
		{
			return false;
		}
		index++;
		numberOfBytesProcessed++;

		_totalDataBytes = pData[index];
		if(_totalDataBytes <= 0)
		{
			return false;
		}
		index++;
		numberOfBytesProcessed++;
	
		for(byte i = 0; i < PACKET_MAX_DATA_LENGTH && index < (pLength - PACKET_END_STREAM_LENGTH); i++)
		{
			_data[i] = pData[index++];
			numberOfDataBytes++;
			numberOfBytesProcessed++;
		}

		numberOfBytesProcessed += PACKET_END_STREAM_LENGTH;
		
		if(numberOfDataBytes != _totalDataBytes || numberOfBytesProcessed != _totalNumberOfBytes)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}

}

#pragma endregion
