#pragma once

#include "GenericBase.h"

template <typename T> class RectangleContainer : public GenericBase
{

	
public:

enum CornerIndex
{
	Bottom,
	Top,
	Left,
	Right,
	TotalCorners
};
	RectangleContainer(void);
	~RectangleContainer(void);

	T GetWidth();

	T GetHeight();

	T* GetCornersArray();

	T GetCorner(CornerIndex pCornerIndex);

	void SetCorner(CornerIndex pCornerIndex, T pValue);

private:

	T _corners[TotalCorners];
};

template <typename T> RectangleContainer<T>::RectangleContainer(void)
{
	_log->Log(std::string("RectangleContainer::ctor - Start"));
	_log->Log(std::string("Initialising corners"));
	for(int i = 0; i < TotalCorners; i++)
	{
		_corners[i] = 0;
	}
	_log->Log(std::string("RectangleContainer::ctor - Finish"));
}


template <typename T> RectangleContainer<T>::~RectangleContainer(void)
{
	_log->Log(std::string("RectangleContainer::dtor - Start"));
	_log->Log(std::string("RectangleContainer::dtor - Finish"));
}

template <typename T> T RectangleContainer<T>::GetWidth()
{
	_log->Log(std::string("RectangleContainer::GetWidth - Start"));
	T width = _corners[Left] - _corners[Right];
	_log->Log(std::string("RectangleContainer::GetWidth - Finish"));
	return width;
}

template <typename T> T RectangleContainer<T>::GetHeight()
{
	_log->Log(std::string("RectangleContainer::GetHeight - Start"));

	T height = _corners[Top] - _corners[Bottom];

	_log->Log(std::string("RectangleContainer::GetHeight - Finish"));

	return height;
}

template <typename T> T* RectangleContainer<T>::GetCornersArray()
{
	_log->Log(std::string("RectangleContainer::GetCornersArray - Start"));
	_log->Log(std::string("RectangleContainer::GetCornersArray - Finish"));
	return _corners;

}

template <typename T> T RectangleContainer<T>::GetCorner(CornerIndex pCornerIndex)
{
	_log->Log(std::string("RectangleContainer::GetCorner - Start"));

	T corner = _corners[pCornerIndex];

	_log->Log(std::string("Returning corner %d", (int)pCornerIndex));
	_log->Log(std::string("RectangleContainer::GetCorner - Finish"));

	return corner;
}

template <typename T> void RectangleContainer<T>::SetCorner(CornerIndex pCornerIndex, T pValue)
{
	_log->Log(std::string("RectangleContainer::SetCorner - Start"));


	_log->Log(std::string("Setting corner %d", (int)pCornerIndex));
	_corners[pCornerIndex] = pValue;

	_log->Log(std::string("RectangleContainer::SetCorner - Finish"));
}


