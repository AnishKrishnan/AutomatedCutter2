#include "BluetoothDebug.h"


BluetoothDebug::BluetoothDebug(SoftwareSerial& pSoftwareSerial) : _serial(pSoftwareSerial)
{
}


BluetoothDebug::~BluetoothDebug(void)
{
}

void BluetoothDebug::Setup(void)
{
	pinMode(BLUETOOTH_RxD, INPUT);
	pinMode(BLUETOOTH_TxD, OUTPUT);
	_serial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
	_serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	_serial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
	_serial.print("\r\n+STPIN=0000\r\n");//Set SLAVE pincode"0000"
	_serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	_serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
	delay(2000); // This delay is required.
	_serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	delay(2000); // This delay is required.
	_serial.flush();
}

void BluetoothDebug::Println(String& pMessage)
{
	_serial.println(pMessage);
}
