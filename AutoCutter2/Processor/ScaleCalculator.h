#pragma once

#include "GenericBase.h"
#include "CustomPoint3d.h"

template <typename T, typename V> class ScaleCalculator :	public GenericBase
{
public:

	ScaleCalculator(void);
	ScaleCalculator(T pOrigLength, V pScaledLength);
	
	void SetScale(T pOrigLength, V pScaledLength);
	CustomPoint3d<V> ScalePoint(CustomPoint3d<T> &pOrigPoint);
	std::vector<CustomPoint3d<V>> ScalePointsList(std::vector<CustomPoint3d<T>>& pOrigList);

private:

	V _scalingFactor;


};

template <typename T, typename V>  ScaleCalculator<T,V>::ScaleCalculator(void)
{
	_log->Log(std::string("ScaleCalculator.ctor - Start"));
	_log->Log(std::string("ScaleCalculator.ctor - Finish"));
}

template <typename T, typename V> ScaleCalculator<T,V>::ScaleCalculator(T pOrigLength, V pScaledLength)
{

	_log->Log(std::string("ScaleCalculator.ctor - Start"));
	_log->Log(std::string("Setting scaling factor"));
	SetScale(pOrigLength, pScaledLength);

	_log->Log(std::string("ScaleCalculator.ctor - Finish"));
}

template <typename T, typename V> void ScaleCalculator<T,V>::SetScale(T pOrigLength, V pScaledLength)
{
	_log->Log(std::string("ScaleCalculator::SetScale - Start"));

	_log->Log(std::string("Calculating scale"));
	V castedOrigLenght = (V)pOrigLength;
	_scalingFactor = pScaledLength / pOrigLength;

	_log->Log(std::string("_scalingFactor = [%f]"), _scalingFactor);

	_log->Log(std::string("ScaleCalculator::SetScale - Finish"));
}

template <typename T, typename V> CustomPoint3d<V> ScaleCalculator<T,V>::ScalePoint(CustomPoint3d<T>& pOrigPoint)
{
	_log->Log(std::string("ScaleCalculator::ScalePoint - Start"));

	V x, y, z;

	_log->Log(std::string("Scaling x coordinate"));
	x = ((V)pOrigPoint.GetX()) * _scalingFactor;

	_log->Log(std::string("Scaling y coordinate"));
	y = ((V)pOrigPoint.GetY()) * _scalingFactor;
	
	_log->Log(std::string("Scaling z coordinate"));
	z = ((V)pOrigPoint.GetZ()) * _scalingFactor;

	_log->Log(std::string("ScaleCalculator::ScalePoint - Finish"));
	return CustomPoint3d<V>(x, y, z);
}

template <typename T, typename V> vector<CustomPoint3d<V>> ScaleCalculator<T,V>::ScalePointsList(vector<CustomPoint3d<T>>& pOrigPointList)
{
	_log->Log(std::string("ScaleCalculator::ScalePointsList - Start"));

	_log->Log(std::string("Creating list of size %i"), pOrigPointList.size());
	vector<CustomPoint3d<V>> pointsList(pOrigPointList.size());

	_log->Log(std::string("Creating points list"));
	for(int i = 0; i < pOrigPointList.size(); i++)
	{
		pointsList.push_back(ScalePoint(pOrigPointList.at(i)));
	}

	_log->Log(std::string("ScaleCalculator::ScalePointsList - Finish"));
	return pointsList;
}
