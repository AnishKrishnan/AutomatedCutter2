#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "IImageInterface.h"
#include "RectangleContainer.h"
#include <climits>
using namespace cv;
class OpenCVImageProcessing : public IImageInterface
{
public:

	OpenCVImageProcessing();

	virtual void OpenFile(std::string& pFileName);

	virtual void DisplayImage();

	virtual void FindOutlines();

	virtual void DrawOutlines();

	virtual IImageContainer& GetImage();

	virtual RectangleContainer<int>& GetBoundingBox();

	virtual vector<vector<CustomPoint3d<int>>>& GetLines();


private:

	//static void TrackBarCallback(int, void*);

	void ExtractContours();

	void FindBoundingBox();

	void ConvertContoursToLines();
	
	Mat _image;
	Mat _grayImage;
	Mat _cannyOutput;
	Mat _contourImage;

	vector<vector<Point>> _contours;
	vector<Vec4i> _hierarchy;

	vector<vector<CustomPoint3d<int>>> _lines;

	static const int RECTANGLE_CORNERS = 4;

	
	RectangleContainer<int> _boundingRectangle;
	const char* _imageWindowName;
	const char* _cannyWindowName;

	//canny variables
	int _lowerThresh, _upperThresh, _maxThresh, _apetureSize;

	double _blendImageAlpha, _blendImageGamma;

	bool _showCanny;
};