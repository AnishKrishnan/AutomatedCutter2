#pragma once
#include "GenericBase.h"
template <typename T> public ref class GenericWrapper
{
public:

	GenericWrapper(T* pInternal);

	T* GetInternal();

private:

	T* _internal;
};

template<typename T> GenericWrapper<T>::GenericWrapper(T* pInternal)
{
	if(pInternal == NULL)
	{
		throw AutoCutterException("GenericWrapper::ctor - pInternal is null");
	}

	_internal = pInternal;
}

template<typename T> T* GenericWrapper<T>::GetInternal()
{
	return _internal;
}