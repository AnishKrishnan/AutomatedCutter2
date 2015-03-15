#pragma once

namespace AutoCutterApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ExecutionProgress
	/// </summary>
	public ref class ExecutionProgress : public System::Windows::Forms::Form
	{
	public:
		ExecutionProgress(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void UpdateOverallProgress(int pPercentage)
		{
			progressBar1->Value = pPercentage;
			if(progressBar1->Style == ProgressBarStyle::Marquee)
			{
				progressBar1->Style = ProgressBarStyle::Blocks;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ExecutionProgress()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  OverallProgressLabel;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->OverallProgressLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 102);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(258, 23);
			this->progressBar1->TabIndex = 0;
			this->progressBar1->Style = ProgressBarStyle::Marquee;
			// 
			// OverallProgressLabel
			// 
			this->OverallProgressLabel->AutoSize = true;
			this->OverallProgressLabel->Location = System::Drawing::Point(13, 79);
			this->OverallProgressLabel->Name = L"OverallProgressLabel";
			this->OverallProgressLabel->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->OverallProgressLabel->Size = System::Drawing::Size(114, 17);
			this->OverallProgressLabel->TabIndex = 1;
			this->OverallProgressLabel->Text = L"Overall Progress";
			// 
			// ExecutionProgress
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->OverallProgressLabel);
			this->Controls->Add(this->progressBar1);
			this->Name = L"ExecutionProgress";
			this->Text = L"ExecutionProgress";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
