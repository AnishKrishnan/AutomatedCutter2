#pragma once
#include "IImageInterface.h"
class FormHelper
{
public:
	FormHelper(void);
	~FormHelper(void);

	static void ShowImage(System::Windows::Forms::PictureBox^ pPictureBox, IImageInterface& pImageProcessor);
};

