#pragma once
#include "GenericBase.h"
#include "CommonHelper.h"
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

static const char PACKET_START_BYTE = 0xFF;
	
static const int PACKET_END_STREAM_LENGTH = 4;
static char PACKET_END_STREAM [] = {0xFF,0xFF,0xFF,0xFF};

class Packet :	public GenericBase
{
public:
	Packet(void);

	char* ConstructPacket(vector<char>& pData);
	char* ConstructPacket();
	bool TryParseDataToPacket(vector<char>& pData);
	
	PacketType GetPacketType();
	void SetPacketType(PacketType pPacketType);

	vector<char>& GetData();
	void SetData(vector<char>& pData);



private:


	char _totalNumberOfBytes;

	PacketType _packetType;

	char _totalDataBytes;

	vector<char> _data, _fullPacketData;
};

