#include "CommsController.h"
#include "Packet.h"

#define LED  13

Packet p1, p2;
char * data = "stuff";
char dataSize = sizeof(data);

char rawPacket[PACKET_MAX_RAW_LENGTH];
bool successfull = false;


void setup()
{

  /* add setup code here */
	p1.SetPacketType(PACKETTYPE_ACK);
	char length = p1.ConstructPacket(rawPacket, data, dataSize);
	if(p2.TryParseDataToPacket(rawPacket, length))
	{
		char recievedData[sizeof(data)];
		p2.GetData(recievedData);

		for(char i = 0; i < sizeof(data); i++)
		{
			if(data[i] != recievedData[i])
			{
				successfull = false;
				break;
			}
			else
			{
				successfull = true;
			}
		}
	}
	pinMode(LED, OUTPUT);
}

void loop()
{

  /* add main program code here */

	if(successfull)
	{
		digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(1000);               // wait for a second
		digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
		delay(1000);
	}

}
