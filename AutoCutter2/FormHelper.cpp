#include "stdafx.h"
#include "FormHelper.h"


FormHelper::FormHelper(void)
{
}

void FormHelper::ShowImage(System::Windows::Forms::PictureBox^ pPictureBox, IImageInterface& pImageProcessor)
{
	IImageContainer& image = pImageProcessor.GetImage();
	System::Drawing::Graphics^ graphics = pPictureBox->CreateGraphics();
	System::IntPtr ptr(image.GetData());
	System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(image.GetWidth(), image.GetHeight(), image.GetStep(), System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr);

	System::Drawing::RectangleF rect(0,0,pPictureBox->Width,pPictureBox->Height);
	graphics->DrawImage(b,rect);
}


FormHelper::~FormHelper(void)
{
}
