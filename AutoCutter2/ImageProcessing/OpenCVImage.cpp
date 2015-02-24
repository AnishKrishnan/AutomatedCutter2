#include "../stdafx.h"
#include "OpenCVImage.h"


OpenCVImage::OpenCVImage(cv::Mat& pImage) : _image(pImage)
{

}


OpenCVImage::~OpenCVImage(void)
{

}

int OpenCVImage::GetWidth()
{
	return _image.size().width;
}

int OpenCVImage::GetHeight()
{
	return _image.size().height;
}

int* OpenCVImage::GetData()
{
	return (int*)_image.data;
}

int OpenCVImage::GetStep()
{
	return _image.step;
}