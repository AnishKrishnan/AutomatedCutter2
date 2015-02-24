#pragma once

#include "GenericBase.h"
#include "IImageContainer.h"
#include "OpenCVImage.h"
#include "RectangleContainer.h"
#include "CustomPoint3d.h"
#include "../stdafx.h"
using namespace std;
class IImageInterface : public GenericBase
{
public:

	virtual ~IImageInterface(void){};

	virtual void OpenFile(std::string& pFileName) = 0;

	virtual void DisplayImage() = 0;

	virtual void FindOutlines() = 0;

	virtual void DrawOutlines() = 0;

	virtual IImageContainer& GetImage() = 0;

	virtual RectangleContainer<int>& GetBoundingBox() = 0;

	virtual vector<vector<CustomPoint3d<int>>>& GetLines() = 0;

};

