#pragma once
#include "CommonHelper.h"
#include "stdlib.h"
#include "Arduino.h"

typedef enum 
{
	PACKETTYPE_INVALID = 0,
	PACKETTYPE_ACK,
	PACKETTYPE_NACK,
	PACKETTYPE_PATH_REQUEST,
	PACKETTYPE_PATH_COMPLETED

}PacketType;

#define IS_VALID_PACKET_TYPE(Type) (Type == PACKETTYPE_ACK			|| \
								    Type == PACKETTYPE_NACK			|| \
									Type == PACKETTYPE_PATH_REQUEST || \
									Type == PACKETTYPE_PATH_COMPLETED  \
									)

#define PACKET_MAX_DATA_LENGTH	100
#define PACKET_MAX_RAW_LENGTH	120

static const byte PACKET_START_BYTE = '%';
	
static const int PACKET_END_STREAM_LENGTH = 4;
static byte PACKET_END_STREAM [] = {'%','%','%','%'};

class Packet
{
public:
	Packet(void);

	byte ConstructPacket(byte * pRawPacket, byte * pData, byte pLength);
	byte ConstructPacket(byte * pRawPacket);
	bool TryParseDataToPacket(byte * pData, byte pLength);
	
	PacketType GetPacketType();
	void SetPacketType(PacketType pPacketType);

	void GetData(byte* pData);
	void SetData(byte * pData, byte pLength);



private:

	byte _totalNumberOfBytes;

	PacketType _packetType;

	byte _totalDataBytes;

	byte _data[PACKET_MAX_DATA_LENGTH];
};

