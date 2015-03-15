#include "GenericBase.h"


SoftwareSerial* GenericBase::_bluetoothSerial = NULL;
BluetoothDebug* GenericBase::_bluetooth = NULL;

GenericBase::GenericBase(void)
{
	if(_bluetoothSerial == NULL)
	{
		_bluetoothSerial = new SoftwareSerial(BLUETOOTH_RxD, BLUETOOTH_TxD);
	}

	if(_bluetooth == NULL)
	{
		_bluetooth = new BluetoothDebug(*_bluetoothSerial);
	}
	Logger::Create(_bluetooth);
	_log = Logger::Instance();
}


GenericBase::~GenericBase(void)
{
}
