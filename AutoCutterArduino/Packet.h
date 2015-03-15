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

static const unsigned char PACKET_START_BYTE = '%';
	
static const int PACKET_END_STREAM_LENGTH = 4;
static unsigned char PACKET_END_STREAM [] = {'%','%','%','%'};

class Packet
{
public:
	Packet(void);

	unsigned char ConstructPacket(unsigned char * pRawPacket, unsigned char * pData, unsigned char pLength);
	unsigned char ConstructPacket(unsigned char * pRawPacket);
	bool TryParseDataToPacket(unsigned char * pData, unsigned char pLength);
	
	PacketType GetPacketType();
	void SetPacketType(PacketType pPacketType);

	void GetData(unsigned char* pData);
	void SetData(unsigned char * pData, unsigned char pLength);



private:

	unsigned char _totalNumberOfBytes;

	PacketType _packetType;

	unsigned char _totalDataBytes;

	unsigned char _data[PACKET_MAX_DATA_LENGTH];
};

