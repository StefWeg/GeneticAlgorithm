#pragma once

namespace GeneticAlgorythm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SplashForm
	/// </summary>
	public ref class SplashForm : public System::Windows::Forms::Form
	{
	public:
		SplashForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SplashForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  label_geneticAlgorythmSign;
	private: System::Windows::Forms::Label^  label_authorSign;

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
			this->label_geneticAlgorythmSign = (gcnew System::Windows::Forms::Label());
			this->label_authorSign = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label_geneticAlgorythmSign
			// 
			this->label_geneticAlgorythmSign->AutoSize = true;
			this->label_geneticAlgorythmSign->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 30, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->label_geneticAlgorythmSign->ForeColor = System::Drawing::Color::White;
			this->label_geneticAlgorythmSign->Location = System::Drawing::Point(54, 130);
			this->label_geneticAlgorythmSign->Name = L"label_geneticAlgorythmSign";
			this->label_geneticAlgorythmSign->Size = System::Drawing::Size(373, 55);
			this->label_geneticAlgorythmSign->TabIndex = 0;
			this->label_geneticAlgorythmSign->Text = L"Genetic Algorythm";
			// 
			// label_authorSign
			// 
			this->label_authorSign->AutoSize = true;
			this->label_authorSign->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_authorSign->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->label_authorSign->Location = System::Drawing::Point(130, 200);
			this->label_authorSign->Name = L"label_authorSign";
			this->label_authorSign->Size = System::Drawing::Size(219, 37);
			this->label_authorSign->TabIndex = 0;
			this->label_authorSign->Text = L"Stefan Wêgrzyn";
			// 
			// SplashForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaGreen;
			this->ClientSize = System::Drawing::Size(480, 380);
			this->ControlBox = false;
			this->Controls->Add(this->label_authorSign);
			this->Controls->Add(this->label_geneticAlgorythmSign);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(480, 380);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(480, 380);
			this->Name = L"SplashForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SplashForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	};
}
