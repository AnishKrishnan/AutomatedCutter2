#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "IImageContainer.h"
class OpenCVImage :	public IImageContainer
{
public:
	OpenCVImage(cv::Mat& pImage);
	~OpenCVImage(void);

	virtual int GetWidth();

	virtual int GetHeight();

	virtual int* GetData();

	virtual int GetStep();

private:
	cv::Mat& _image;
};

