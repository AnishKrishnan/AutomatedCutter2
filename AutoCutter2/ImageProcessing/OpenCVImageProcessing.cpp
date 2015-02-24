#include "../stdafx.h"
#include "OpenCVImageProcessing.h"


OpenCVImageProcessing::OpenCVImageProcessing()
{
	
	_log->Log(std::string("OpenCVImageProcessing::ctor - Start"));

	_log->Log(std::string("Retrieving image window name from config"));
	_imageWindowName = _config->getValue("ImageWindowName").c_str();
	
	_log->Log(std::string("Retrieving show canny flag from config"));
	std::string showCannyString = _config->getValue("ShowCannyImage");

	if(!showCannyString.empty() && showCannyString.compare("True") == 0)
	{
		_log->Log(std::string("Show canny is set to true, will proceed to retrieve canny window name"));
		_showCanny = true;
		_cannyWindowName = _config->getValue("CannyImageName").c_str();
	}

	_log->Log(std::string("Reading canny thresholds from config"));
	_lowerThresh = atoi(_config->getValue("LowerThresh").c_str());
	_upperThresh = atoi(_config->getValue("UpperThresh").c_str());
	_maxThresh = atoi(_config->getValue("MaxThresh").c_str());
	_apetureSize = atoi(_config->getValue("ApetureSize").c_str());

	_log->Log(std::string("Reading blend image values"));
	_blendImageAlpha = atof(_config->getValue("ImageBlendAlpha").c_str());
	_blendImageGamma = atof(_config->getValue("ImageBlendGamma").c_str());

	_log->Log(std::string("OpenCVImageProcessing::ctor - Finish"));
}


void OpenCVImageProcessing::OpenFile(std::string& pFileName)
{
	_log->Log(std::string("OpenCVImageProcessing::OpenFile - Start"));

	if(pFileName.empty())
	{
		throw AutoCutterException("String name is null or empty");
	}
	_image = imread(pFileName);
	
	_log->Log(std::string("OpenCVImageProcessing::OpenFile - Finish"));
}

void OpenCVImageProcessing::DisplayImage()
{
	_log->Log(std::string("OpenCVImageProcessing::DisplayImage - Start"));
	imshow(_imageWindowName, _image);

	_log->Log(std::string("OpenCVImageProcessing::DisplayImage - Finish"));
}

void OpenCVImageProcessing::FindOutlines()
{
	_log->Log(std::string("OpenCVImageProcessing::FindOutlines - Start"));
	
	_log->Log(std::string("Converting original image to grayscale"));
	cvtColor(_image, _grayImage, CV_BGR2GRAY);

	//doing this because it said so at http://docs.opencv.org/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
	_log->Log(std::string("blurring image"));
	blur(_grayImage, _grayImage, Size(3,3));

	_log->Log(std::string("Setting trackbars"));

	
	ExtractContours();

	_log->Log(std::string("Finding bounding box"));
	FindBoundingBox();

	_log->Log(std::string("Converting lines to box"));
	ConvertContoursToLines();

	_log->Log(std::string("OpenCVImageProcessing::FindOutlines - Finish"));
}

void OpenCVImageProcessing::ExtractContours()
{
	Canny(_grayImage, _cannyOutput, _lowerThresh, _upperThresh, _apetureSize);
	findContours(_cannyOutput, _contours, _hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
}


//void OpenCVImageProcessing::TrackBarCallback(int, void* pObject)
//{
//	if(!pObject)
//	{
//		throw AutoCutterException("pObject is null");
//	}
//	OpenCVImageProcessing* imageProcessor = (OpenCVImageProcessing*)pObject;
//	Canny(imageProcessor->_grayImage, imageProcessor->_cannyOutput, imageProcessor->_lowerThresh, imageProcessor->_upperThresh, imageProcessor->_apetureSize);
//
//	findContours(imageProcessor->_cannyOutput, imageProcessor->_contours, imageProcessor->_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
//	
//}

void OpenCVImageProcessing::DrawOutlines()
{
	_log->Log(std::string("OpenCVImageProcessing::DrawOutlines - Start"));

	_log->Log(std::string("Drawing contours"));

	_contourImage = Mat::zeros(_cannyOutput.size(), CV_8UC3);
	Scalar white(255,255,255);
	_contourImage.setTo(white);
	Scalar colour(0, 0, 127);
	for(int i = 0; i < _contours.size(); i++)
	{
		drawContours(_contourImage, _contours, i, colour, 2, 8, _hierarchy, 0, Point());
	}

	_log->Log(std::string("Drawing bounding rectangle"));
	Scalar boundingColour(127,0,0);
	Point topLeft(_boundingRectangle.GetCorner(RectangleContainer<int>::Left),_boundingRectangle.GetCorner(RectangleContainer<int>::Top));
	Point bottomRight(_boundingRectangle.GetCorner(RectangleContainer<int>::Right),_boundingRectangle.GetCorner(RectangleContainer<int>::Bottom));

	rectangle(_contourImage, topLeft, bottomRight, boundingColour, 2, 8, 0);

	_log->Log(std::string("Blending images together"));
	double beta = 1.0 - _blendImageAlpha;
	addWeighted(_image, _blendImageAlpha, _contourImage, beta, _blendImageGamma, _image);
	
	_log->Log(std::string("OpenCVImageProcessing::DrawOutlines - Finish"));
}

IImageContainer& OpenCVImageProcessing::GetImage()
{
	_log->Log(std::string("OpenCVImageProcessing::GetImage - Start"));

	_log->Log(std::string("Creating OpenCVImage object"));
	OpenCVImage* image = new OpenCVImage(_image);

	_log->Log(std::string("OpenCVImageProcessing::GetImage - Finish"));
	return *image;
}

void OpenCVImageProcessing::FindBoundingBox()
{
	_log->Log(std::string("OpenCVImageProcessing::FindBoundingBox - Start"));

	int top = INT_MIN, right = INT_MIN;
	int left = INT_MAX, bottom = INT_MAX;
	Point contourPoint;

	_log->Log(std::string("Finding bounding box for contours"));
	for(int i = 0; i < _contours.size(); i++)
	{
		_log->Log(std::string("Processing line %d"), i);
		for(int j = 0; j < _contours[i].size(); j++)
		{
			contourPoint = _contours[i][j];

			left = min(contourPoint.x, left);
			right = max(contourPoint.x, right);
			bottom = min(contourPoint.y, bottom);
			top = max(contourPoint.y, top);

		}
	}

	_log->Log(std::string("Rectangle is: [left=%d], [right=%d], [bottom=%d], [top=%d]"), left, right, bottom, top);
	
	_boundingRectangle.SetCorner(RectangleContainer<int>::Left, left);
	_boundingRectangle.SetCorner(RectangleContainer<int>::Right, right);
	_boundingRectangle.SetCorner(RectangleContainer<int>::Bottom, bottom);
	_boundingRectangle.SetCorner(RectangleContainer<int>::Top, top);

	_log->Log(std::string("OpenCVImageProcessing::FindBoundingBox - Finish"));
}

RectangleContainer<int>& OpenCVImageProcessing::GetBoundingBox()
{
	return _boundingRectangle;
}

vector<vector<CustomPoint3d<int>>>& OpenCVImageProcessing::GetLines()
{
	_log->Log(std::string("OpenCVImageProcessing::GetLines - Start"));


	_log->Log(std::string("OpenCVImageProcessing::GetLines - Finish"));
	return _lines;
}

void OpenCVImageProcessing::ConvertContoursToLines()
{
	_log->Log(std::string("OpenCVImageProcessing::ConvertContoursToLines - Start"));

	_log->Log(std::string("Processing contours"));
	for(int i = 0; i < _contours.size(); i++)
	{
		_log->Log(std::string("Processing contour %i"), i);
		vector<CustomPoint3d<int>> line;
		for(int j = 0; j < _contours.at(i).size(); j++)
		{
			CustomPoint3d<int> point;
			point.SetX(_contours.at(i).at(j).x);
			point.SetY(_contours.at(i).at(j).y);

			line.push_back(point);
		}

		_lines.push_back(line);

	}
	_log->Log(std::string("OpenCVImageProcessing::ConvertContoursToLines - Finish"));
}
