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

static const unsigned char PACKET_START_BYTE = '%';
	
static const int PACKET_END_STREAM_LENGTH = 4;
static unsigned char PACKET_END_STREAM [] = {'%','%','%','%'};

class Packet :	public GenericBase
{
public:
	Packet(void);

	uchar_array_t ConstructPacket(vector<unsigned char>& pData);
	uchar_array_t ConstructPacket();
	bool TryParseDataToPacket(vector<unsigned char>& pData);
	
	PacketType GetPacketType();
	void SetPacketType(PacketType pPacketType);

	vector<unsigned char>& GetData();
	void SetData(vector<unsigned char>& pData);



private:


	unsigned char _totalNumberOfBytes;

	PacketType _packetType;

	unsigned char _totalDataBytes;

	vector<unsigned char> _data, _fullPacketData;
};

