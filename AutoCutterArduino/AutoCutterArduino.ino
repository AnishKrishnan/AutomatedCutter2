#include <SoftwareSerial.h>
#include "CommsController.h"
#include "Packet.h"

CommsController _comms(Serial);

void setup()
{

  /* add setup code here */
	pinMode(13, OUTPUT);
	_comms.OpenConnection();
}

void loop()
{

  /* add main program code here */
	_comms.ProcessOutbox();

}

void serialEvent()
{
	while(Serial.available())
	{
		_comms.RecievedByte((unsigned char)Serial.read());
	}
}