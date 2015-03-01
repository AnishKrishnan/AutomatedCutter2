#pragma once
#include "stdlib.h"
template<typename T> class Queue
{
public:
	Queue<T>(int pNoOfElements);

	T Pop();
	T Peek();
	void Push(T& pElement);
	int Size();
	bool IsEmpty();
	bool IsFull();

private:
	
	T * _elements;

	int _elementCount;
	int _maxCount;

	int _head, _tail;
};

template <typename T> Queue<T>::Queue(int pNoOfElements)
{
	if(pNoOfElements > 0)
	{
		_elements = (T*)malloc(sizeof(T) * pNoOfElements);
		_elementCount = 0;
		_maxCount = pNoOfElements;
		_head = 0;
		_tail = 0;

	}
}

template <typename T> T Queue<T>::Pop()
{
	T headElement = Peek();

	_elementCount--;
	_head = (_head + 1) % _maxCount;

	return headElement;
}

template <typename T> T Queue<T>::Peek()
{
	T headElement;

	if(!IsEmpty())
	{
		headElement = _elements[_head];
	}

	return headElement;
}

template <typename T> void Queue<T>::Push(T& pElement)
{
	if(!IsFull())
	{
		_elements[_tail] = pElement;
		_elementCount++;
		_tail = (_tail + 1) % _maxCount;
	}
}

template <typename T> bool Queue<T>::IsEmpty()
{
	return _elementCount == 0;
}

template <typename T> bool Queue<T>::IsFull()
{
	return _elementCount > _maxCount;
}

template <typename T> int Queue<T>::Size()
{
	return _elementCount;
}