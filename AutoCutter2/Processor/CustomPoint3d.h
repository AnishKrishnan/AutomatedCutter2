#pragma once
#include "GenericBase.h"

template <typename T> class CustomPoint3d :	public GenericBase
{
public:

#pragma region Constructors and Destructors

	CustomPoint3d<T>(void);
	CustomPoint3d<T>(T pX, T pY, T pZ);

#pragma endregion

#pragma region Accessors and Mutators

	T GetX();
	T GetY();
	T GetZ();

	void SetX(T pX);
	void SetY(T pY);
	void SetZ(T pZ);

#pragma endregion

private:
	T _x;
	T _y;
	T _z;
};

#pragma region Constructors and Destructors Implementation
template <typename T> CustomPoint3d<T>::CustomPoint3d(void)
{

}

template <typename T> CustomPoint3d<T>::CustomPoint3d(T pX, T pY, T pZ)
{
	_log->Log(std::string("CustomPoint3d::ctor - Start"));
	_log->Log(std::string("CustomPoint3d::ctor - assigning x, y and z"));
	_x = pX;
	_y = pY;
	_z = pZ;
	_log->Log(std::string("CustomPoint3d::ctor - Finish"));
}
#pragma endregion

#pragma region Accessor Implementation

template <typename T> T CustomPoint3d<T>::GetX()
{

	return _x;
}

template <typename T> T CustomPoint3d<T>::GetY()
{
	return _y;
}

template <typename T> T CustomPoint3d<T>::GetZ()
{
	return _z;
}

#pragma endregion

#pragma region Mutator Implementation 

template <typename T> void CustomPoint3d<T>::SetX(T pX)
{
	_x = pX;
}

template <typename T> void CustomPoint3d<T>::SetY(T pY)
{
	_y = pY;
}

template <typename T> void CustomPoint3d<T>::SetZ(T pZ)
{
	_z = pZ;
}
#pragma endregion

