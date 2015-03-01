#pragma once

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

static const char PACKET_START_BYTE = 0xFF;
	
static const int PACKET_END_STREAM_LENGTH = 4;
static char PACKET_END_STREAM [] = {0xFF,0xFF,0xFF,0xFF};

class Packet
{
public:
	Packet(void);

	char ConstructPacket(char * pRawPacket, char * pData, char pLength);
	char ConstructPacket(char * pRawPacket);
	bool TryParseDataToPacket(char * pData, char pLength);
	
	PacketType GetPacketType();
	void SetPacketType(PacketType pPacketType);

	void GetData(char* pData);
	void SetData(char * pData, char pLength);



private:

	void ClearData(char * pData, char pLength);


	char _totalNumberOfBytes;

	PacketType _packetType;

	char _totalDataBytes;

	char _data[PACKET_MAX_DATA_LENGTH];
};

