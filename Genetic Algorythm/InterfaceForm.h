#pragma once

#include "GeneticAlgorythmEngine.h"
#include "SplashForm.h"
#include "ConfigurationForm.h"


namespace GeneticAlgorythm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	// DELEGATE DECLARATION ----------------------------------------------------------------------------

	// following delegate is needed for handling 'ToSettings' event (used in 'TOSETTINGS EVENT' segment below)
	// delegate is an object which stores information about how function should look like (accepted parameters and returned type)
	public delegate void ToSettingsEventHandler(Parameters^ passedConfig);

	// -------------------------------------------------------------------------------------------------



	// CONSTRUCTOR & DESTRUCTOR ------------------------------------------------------------------------

	/// <summary>
	/// Summary for InterfaceForm
	/// </summary>
	public ref class InterfaceForm : public System::Windows::Forms::Form
	{
	public:
		InterfaceForm(void)
		{
			InitializeComponent();
			// CONSTRUCTOR
			this->Config = gcnew Parameters();
			this->Individuals = gcnew Population(Config);
			this->Visualization = gcnew Chart(Config, Individuals);
			this->Toolbox = gcnew GeneticAlgorythmToolbox(Config);

			this->ToSettingsEventManager = nullptr;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InterfaceForm()
		{
			if (components)
			{
				delete components;
			}
		}

	// -------------------------------------------------------------------------------------------------


	// INTERNAL FIELDS ---------------------------------------------------------------------------------

	private: Parameters^ Config;
	private: Population^ Individuals;
	private: Chart^ Visualization;
	private: GeneticAlgorythmToolbox^ Toolbox;
	private: int generationQuantity;
	private: int generationIndex;
	private: double realizationAtBeginning;
	private: array<Chart^> ^history;

	// -------------------------------------------------------------------------------------------------


	// TOSETTINGS EVENT --------------------------------------------------------------------------------

	// creating event manager storing adressess to delegates
	private: ToSettingsEventHandler^ ToSettingsEventManager;

	// creating event ToSettings with required support methods
	public: event ToSettingsEventHandler^ ToSettings {
		void add(ToSettingsEventHandler^ del) { // adding new delegate to event manager associated with event
			this->ToSettingsEventManager = static_cast<ToSettingsEventHandler^>(Delegate::Combine(this->ToSettingsEventManager, del));
		}
		void remove(ToSettingsEventHandler^ del) { // removing delegate from event manager associated with event
			this->ToSettingsEventManager = static_cast<ToSettingsEventHandler^>(Delegate::Remove(this->ToSettingsEventManager, del));
		}
		void raise(Parameters^ passedConfig) { // runs delegate functions using passed argument
			if (this->ToSettingsEventManager != nullptr) {
				this->ToSettingsEventManager->Invoke(passedConfig);
			}
		}
	} // event used in 'button_configuration_Click' method below ('CONFIGURATION WINDOW OPENING' segment)

	// -------------------------------------------------------------------------------------------------


	// PRIVATE APPLYCONFIGURATION METHOD ----------------------------------------------------------------

	// 'ApplyConfiguration' method is delegate of the 'FromSettings' event from 'ConfigurationForm.h'
	private: void ApplyConfiguration(Parameters^ passedConfig) {

		// creating new Config, Individuals, Visualization & Toolbox
		this->Config = gcnew Parameters(passedConfig);
		this->Individuals = gcnew Population(Config);
		this->Visualization = gcnew Chart(Config, Individuals);
		this->Toolbox = gcnew GeneticAlgorythmToolbox(Config);

		// clearing previous chart and creating new one
		this->chart_visualization->Series["Series_axisX"]->Points->Clear();
		this->chart_visualization->Series["Series_axisY"]->Points->Clear();
		chartAreaSetUp();
		this->chart_visualization->Series["Series_parabola"]->Points->Clear();
		drawParabola();
		this->chart_visualization->Series["Series_points"]->Points->Clear();
		drawPoints();
		// blocking previous and next buttons
		button_newGeneration->Enabled = true;
		this->button_previous->Enabled = false;
		this->button_next->Enabled = false;

		// setting internal fields
		this->generationQuantity = 1;
		this->generationIndex = 0;
		this->history = gcnew array<Chart^>(999);
		this->history[generationIndex] = Visualization;
		this->realizationAtBeginning = Visualization->RealizationPercentage;
		informationSetUp();

		this->ToSettingsEventManager = nullptr;
	}

	// -------------------------------------------------------------------------------------------------


	// PRIVATE ENABLEWINDOW METHOD ---------------------------------------------------------------------

	// 'EnableWindow' method is delegate of the 'WindowClosed' event from 'ConfigurationForm.h'
	private: void EnableWindow() {
		// unblocking main window
		this->Enabled = true;
	}

	// -------------------------------------------------------------------------------------------------


	// INTERFACE CONTROLS DECLARATIONS -----------------------------------------------------------------

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart_visualization;
	private: System::Windows::Forms::Panel^  panel_chart;
	private: System::Windows::Forms::Button^  button_configuration;
	private: System::Windows::Forms::Panel^  panel_controls;
	private: System::Windows::Forms::Panel^  panel_progressBar;
	private: System::Windows::Forms::ProgressBar^  progressBar_realization;

	private: System::Windows::Forms::Button^  button_next;
	private: System::Windows::Forms::Button^  button_previous;
	private: System::Windows::Forms::Button^  button_restart;
	private: System::Windows::Forms::Button^  button_newGeneration;
	private: System::Windows::Forms::Label^  label_genNum;
	private: System::Windows::Forms::Label^  label_genNumSign;
	private: System::Windows::Forms::Label^  label_bestIndividual;
	private: System::Windows::Forms::Label^  label_bestIndividualSign;
	private: System::Windows::Forms::Label^  label_target;
	private: System::Windows::Forms::Label^  label_targetSign;
	private: System::Windows::Forms::Label^  label_average;
	private: System::Windows::Forms::Label^  label_targetValue;
	private: System::Windows::Forms::Label^  label_averageSign;
	private: System::Windows::Forms::Label^  label_targetTypeSign;
	private: System::Windows::Forms::Label^  label_percentageSign;
	private: System::Windows::Forms::Label^  label_realizationSign;
	private: System::Windows::Forms::Label^  label_realization;

	private: System::Windows::Forms::GroupBox^  groupBox_controls;
	private: System::Windows::Forms::GroupBox^  groupBox_info;
	private: System::Windows::Forms::GroupBox^  groupBox_progressBar;
	private: System::Windows::Forms::GroupBox^  groupBox_quit;
	private: System::Windows::Forms::Button^  button_quit;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	// -------------------------------------------------------------------------------------------------


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart_visualization = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->panel_chart = (gcnew System::Windows::Forms::Panel());
			this->button_configuration = (gcnew System::Windows::Forms::Button());
			this->panel_controls = (gcnew System::Windows::Forms::Panel());
			this->groupBox_quit = (gcnew System::Windows::Forms::GroupBox());
			this->button_quit = (gcnew System::Windows::Forms::Button());
			this->label_realization = (gcnew System::Windows::Forms::Label());
			this->label_percentageSign = (gcnew System::Windows::Forms::Label());
			this->label_realizationSign = (gcnew System::Windows::Forms::Label());
			this->label_average = (gcnew System::Windows::Forms::Label());
			this->label_targetValue = (gcnew System::Windows::Forms::Label());
			this->label_averageSign = (gcnew System::Windows::Forms::Label());
			this->label_targetTypeSign = (gcnew System::Windows::Forms::Label());
			this->label_target = (gcnew System::Windows::Forms::Label());
			this->label_targetSign = (gcnew System::Windows::Forms::Label());
			this->label_bestIndividual = (gcnew System::Windows::Forms::Label());
			this->label_bestIndividualSign = (gcnew System::Windows::Forms::Label());
			this->label_genNum = (gcnew System::Windows::Forms::Label());
			this->label_genNumSign = (gcnew System::Windows::Forms::Label());
			this->button_next = (gcnew System::Windows::Forms::Button());
			this->button_previous = (gcnew System::Windows::Forms::Button());
			this->button_restart = (gcnew System::Windows::Forms::Button());
			this->button_newGeneration = (gcnew System::Windows::Forms::Button());
			this->groupBox_controls = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox_info = (gcnew System::Windows::Forms::GroupBox());
			this->panel_progressBar = (gcnew System::Windows::Forms::Panel());
			this->progressBar_realization = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox_progressBar = (gcnew System::Windows::Forms::GroupBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_visualization))->BeginInit();
			this->panel_controls->SuspendLayout();
			this->groupBox_quit->SuspendLayout();
			this->panel_progressBar->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart_visualization
			// 
			this->chart_visualization->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->Name = L"ChartArea_visualization";
			chartArea1->Position->Auto = false;
			chartArea1->Position->Height = 97;
			chartArea1->Position->Width = 99;
			chartArea1->Position->Y = 2;
			this->chart_visualization->ChartAreas->Add(chartArea1);
			this->chart_visualization->Location = System::Drawing::Point(10, 10);
			this->chart_visualization->Name = L"chart_visualization";
			series1->BorderWidth = 2;
			series1->ChartArea = L"ChartArea_visualization";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::SystemColors::MenuHighlight;
			series1->IsVisibleInLegend = false;
			series1->Name = L"Series_parabola";
			series2->ChartArea = L"ChartArea_visualization";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series2->IsVisibleInLegend = false;
			series2->MarkerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series2->MarkerBorderWidth = 2;
			series2->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series2->MarkerSize = 7;
			series2->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series2->Name = L"Series_points";
			series3->BorderWidth = 2;
			series3->ChartArea = L"ChartArea_visualization";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Black;
			series3->Name = L"Series_axisX";
			series4->BorderWidth = 2;
			series4->ChartArea = L"ChartArea_visualization";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Black;
			series4->Name = L"Series_axisY";
			this->chart_visualization->Series->Add(series1);
			this->chart_visualization->Series->Add(series2);
			this->chart_visualization->Series->Add(series3);
			this->chart_visualization->Series->Add(series4);
			this->chart_visualization->Size = System::Drawing::Size(980, 630);
			this->chart_visualization->TabIndex = 0;
			this->chart_visualization->Text = L"visualization";
			// 
			// panel_chart
			// 
			this->panel_chart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel_chart->Location = System::Drawing::Point(0, 0);
			this->panel_chart->Name = L"panel_chart";
			this->panel_chart->Size = System::Drawing::Size(1000, 645);
			this->panel_chart->TabIndex = 0;
			// 
			// button_configuration
			// 
			this->button_configuration->Location = System::Drawing::Point(10, 30);
			this->button_configuration->Name = L"button_configuration";
			this->button_configuration->Size = System::Drawing::Size(120, 30);
			this->button_configuration->TabIndex = 1;
			this->button_configuration->Text = L"Configuration";
			this->button_configuration->UseVisualStyleBackColor = true;
			this->button_configuration->Click += gcnew System::EventHandler(this, &InterfaceForm::button_configuration_Click);
			// 
			// panel_controls
			// 
			this->panel_controls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel_controls->Controls->Add(this->groupBox_quit);
			this->panel_controls->Controls->Add(this->label_realization);
			this->panel_controls->Controls->Add(this->label_percentageSign);
			this->panel_controls->Controls->Add(this->label_realizationSign);
			this->panel_controls->Controls->Add(this->label_average);
			this->panel_controls->Controls->Add(this->label_targetValue);
			this->panel_controls->Controls->Add(this->label_averageSign);
			this->panel_controls->Controls->Add(this->label_targetTypeSign);
			this->panel_controls->Controls->Add(this->label_target);
			this->panel_controls->Controls->Add(this->label_targetSign);
			this->panel_controls->Controls->Add(this->label_bestIndividual);
			this->panel_controls->Controls->Add(this->label_bestIndividualSign);
			this->panel_controls->Controls->Add(this->label_genNum);
			this->panel_controls->Controls->Add(this->label_genNumSign);
			this->panel_controls->Controls->Add(this->button_next);
			this->panel_controls->Controls->Add(this->button_previous);
			this->panel_controls->Controls->Add(this->button_restart);
			this->panel_controls->Controls->Add(this->button_newGeneration);
			this->panel_controls->Controls->Add(this->button_configuration);
			this->panel_controls->Controls->Add(this->groupBox_controls);
			this->panel_controls->Controls->Add(this->groupBox_info);
			this->panel_controls->Location = System::Drawing::Point(1000, 0);
			this->panel_controls->Name = L"panel_controls";
			this->panel_controls->Size = System::Drawing::Size(150, 710);
			this->panel_controls->TabIndex = 0;
			// 
			// groupBox_quit
			// 
			this->groupBox_quit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox_quit->Controls->Add(this->button_quit);
			this->groupBox_quit->Location = System::Drawing::Point(0, 645);
			this->groupBox_quit->Name = L"groupBox_quit";
			this->groupBox_quit->Size = System::Drawing::Size(140, 55);
			this->groupBox_quit->TabIndex = 6;
			this->groupBox_quit->TabStop = false;
			// 
			// button_quit
			// 
			this->button_quit->Location = System::Drawing::Point(10, 15);
			this->button_quit->Name = L"button_quit";
			this->button_quit->Size = System::Drawing::Size(120, 30);
			this->button_quit->TabIndex = 0;
			this->button_quit->Text = L"Quit";
			this->button_quit->UseVisualStyleBackColor = true;
			this->button_quit->Click += gcnew System::EventHandler(this, &InterfaceForm::button_quit_Click);
			// 
			// label_realization
			// 
			this->label_realization->Location = System::Drawing::Point(84, 365);
			this->label_realization->Name = L"label_realization";
			this->label_realization->Size = System::Drawing::Size(35, 13);
			this->label_realization->TabIndex = 0;
			this->label_realization->Text = L"30.21";
			this->label_realization->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_percentageSign
			// 
			this->label_percentageSign->Location = System::Drawing::Point(116, 365);
			this->label_percentageSign->Name = L"label_percentageSign";
			this->label_percentageSign->Size = System::Drawing::Size(14, 13);
			this->label_percentageSign->TabIndex = 0;
			this->label_percentageSign->Text = L"%";
			this->label_percentageSign->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_realizationSign
			// 
			this->label_realizationSign->Location = System::Drawing::Point(10, 365);
			this->label_realizationSign->Name = L"label_realizationSign";
			this->label_realizationSign->Size = System::Drawing::Size(74, 13);
			this->label_realizationSign->TabIndex = 0;
			this->label_realizationSign->Text = L"Realization:";
			this->label_realizationSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label_average
			// 
			this->label_average->Location = System::Drawing::Point(80, 320);
			this->label_average->Name = L"label_average";
			this->label_average->Size = System::Drawing::Size(50, 13);
			this->label_average->TabIndex = 0;
			this->label_average->Text = L"1054.74";
			this->label_average->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_targetValue
			// 
			this->label_targetValue->Location = System::Drawing::Point(80, 340);
			this->label_targetValue->Name = L"label_targetValue";
			this->label_targetValue->Size = System::Drawing::Size(50, 13);
			this->label_targetValue->TabIndex = 0;
			this->label_targetValue->Text = L"1234.56";
			this->label_targetValue->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_averageSign
			// 
			this->label_averageSign->Location = System::Drawing::Point(10, 320);
			this->label_averageSign->Name = L"label_averageSign";
			this->label_averageSign->Size = System::Drawing::Size(70, 13);
			this->label_averageSign->TabIndex = 0;
			this->label_averageSign->Text = L"Average:";
			this->label_averageSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label_targetTypeSign
			// 
			this->label_targetTypeSign->Location = System::Drawing::Point(10, 340);
			this->label_targetTypeSign->Name = L"label_targetTypeSign";
			this->label_targetTypeSign->Size = System::Drawing::Size(70, 13);
			this->label_targetTypeSign->TabIndex = 0;
			this->label_targetTypeSign->Text = L"Maximum:";
			this->label_targetTypeSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label_target
			// 
			this->label_target->Location = System::Drawing::Point(88, 295);
			this->label_target->Name = L"label_target";
			this->label_target->Size = System::Drawing::Size(42, 13);
			this->label_target->TabIndex = 0;
			this->label_target->Text = L"30.06";
			this->label_target->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_targetSign
			// 
			this->label_targetSign->Location = System::Drawing::Point(10, 295);
			this->label_targetSign->Name = L"label_targetSign";
			this->label_targetSign->Size = System::Drawing::Size(70, 13);
			this->label_targetSign->TabIndex = 0;
			this->label_targetSign->Text = L"Target:";
			this->label_targetSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label_bestIndividual
			// 
			this->label_bestIndividual->Location = System::Drawing::Point(88, 275);
			this->label_bestIndividual->Name = L"label_bestIndividual";
			this->label_bestIndividual->Size = System::Drawing::Size(42, 13);
			this->label_bestIndividual->TabIndex = 0;
			this->label_bestIndividual->Text = L"30.21";
			this->label_bestIndividual->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_bestIndividualSign
			// 
			this->label_bestIndividualSign->AutoSize = true;
			this->label_bestIndividualSign->Location = System::Drawing::Point(10, 275);
			this->label_bestIndividualSign->Name = L"label_bestIndividualSign";
			this->label_bestIndividualSign->Size = System::Drawing::Size(78, 13);
			this->label_bestIndividualSign->TabIndex = 0;
			this->label_bestIndividualSign->Text = L"Best individual:";
			this->label_bestIndividualSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label_genNum
			// 
			this->label_genNum->Location = System::Drawing::Point(105, 250);
			this->label_genNum->Name = L"label_genNum";
			this->label_genNum->Size = System::Drawing::Size(25, 13);
			this->label_genNum->TabIndex = 0;
			this->label_genNum->Text = L"1";
			this->label_genNum->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_genNumSign
			// 
			this->label_genNumSign->AutoSize = true;
			this->label_genNumSign->Location = System::Drawing::Point(10, 250);
			this->label_genNumSign->Name = L"label_genNumSign";
			this->label_genNumSign->Size = System::Drawing::Size(100, 13);
			this->label_genNumSign->TabIndex = 0;
			this->label_genNumSign->Text = L"Generation number:";
			this->label_genNumSign->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button_next
			// 
			this->button_next->Enabled = false;
			this->button_next->Location = System::Drawing::Point(70, 120);
			this->button_next->Name = L"button_next";
			this->button_next->Size = System::Drawing::Size(60, 30);
			this->button_next->TabIndex = 4;
			this->button_next->Text = L"Next";
			this->button_next->UseVisualStyleBackColor = true;
			this->button_next->Click += gcnew System::EventHandler(this, &InterfaceForm::button_next_Click);
			// 
			// button_previous
			// 
			this->button_previous->Enabled = false;
			this->button_previous->Location = System::Drawing::Point(10, 120);
			this->button_previous->Name = L"button_previous";
			this->button_previous->Size = System::Drawing::Size(60, 30);
			this->button_previous->TabIndex = 3;
			this->button_previous->Text = L"Previous";
			this->button_previous->UseVisualStyleBackColor = true;
			this->button_previous->Click += gcnew System::EventHandler(this, &InterfaceForm::button_previous_Click);
			// 
			// button_restart
			// 
			this->button_restart->Location = System::Drawing::Point(10, 170);
			this->button_restart->Name = L"button_restart";
			this->button_restart->Size = System::Drawing::Size(120, 30);
			this->button_restart->TabIndex = 5;
			this->button_restart->Text = L"Restart";
			this->button_restart->UseVisualStyleBackColor = true;
			this->button_restart->Click += gcnew System::EventHandler(this, &InterfaceForm::button_restart_Click);
			// 
			// button_newGeneration
			// 
			this->button_newGeneration->Location = System::Drawing::Point(10, 80);
			this->button_newGeneration->Name = L"button_newGeneration";
			this->button_newGeneration->Size = System::Drawing::Size(120, 30);
			this->button_newGeneration->TabIndex = 2;
			this->button_newGeneration->Text = L"New generation";
			this->button_newGeneration->UseVisualStyleBackColor = true;
			this->button_newGeneration->Click += gcnew System::EventHandler(this, &InterfaceForm::button_newGeneration_Click);
			// 
			// groupBox_controls
			// 
			this->groupBox_controls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox_controls->Location = System::Drawing::Point(0, 10);
			this->groupBox_controls->Name = L"groupBox_controls";
			this->groupBox_controls->Size = System::Drawing::Size(140, 200);
			this->groupBox_controls->TabIndex = 1;
			this->groupBox_controls->TabStop = false;
			this->groupBox_controls->Text = L"Controls";
			// 
			// groupBox_info
			// 
			this->groupBox_info->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox_info->Location = System::Drawing::Point(0, 230);
			this->groupBox_info->Name = L"groupBox_info";
			this->groupBox_info->Size = System::Drawing::Size(140, 160);
			this->groupBox_info->TabIndex = 0;
			this->groupBox_info->TabStop = false;
			this->groupBox_info->Text = L"Information";
			// 
			// panel_progressBar
			// 
			this->panel_progressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel_progressBar->Controls->Add(this->progressBar_realization);
			this->panel_progressBar->Controls->Add(this->groupBox_progressBar);
			this->panel_progressBar->Location = System::Drawing::Point(0, 645);
			this->panel_progressBar->Name = L"panel_progressBar";
			this->panel_progressBar->Size = System::Drawing::Size(1000, 65);
			this->panel_progressBar->TabIndex = 0;
			// 
			// progressBar_realization
			// 
			this->progressBar_realization->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar_realization->Location = System::Drawing::Point(20, 20);
			this->progressBar_realization->Name = L"progressBar_realization";
			this->progressBar_realization->Size = System::Drawing::Size(960, 23);
			this->progressBar_realization->Step = 1;
			this->progressBar_realization->TabIndex = 0;
			// 
			// groupBox_progressBar
			// 
			this->groupBox_progressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox_progressBar->Location = System::Drawing::Point(10, 0);
			this->groupBox_progressBar->Name = L"groupBox_progressBar";
			this->groupBox_progressBar->Size = System::Drawing::Size(980, 55);
			this->groupBox_progressBar->TabIndex = 0;
			this->groupBox_progressBar->TabStop = false;
			this->groupBox_progressBar->Text = L"Progress";
			// 
			// InterfaceForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1150, 710);
			this->Controls->Add(this->panel_progressBar);
			this->Controls->Add(this->chart_visualization);
			this->Controls->Add(this->panel_chart);
			this->Controls->Add(this->panel_controls);
			this->MinimumSize = System::Drawing::Size(1166, 749);
			this->Name = L"InterfaceForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Genetic Algorythm";
			this->Load += gcnew System::EventHandler(this, &InterfaceForm::InterfaceForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_visualization))->EndInit();
			this->panel_controls->ResumeLayout(false);
			this->panel_controls->PerformLayout();
			this->groupBox_quit->ResumeLayout(false);
			this->panel_progressBar->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	// method launching thread 'splashThread'
	private: System::Void splash() {
		Application::Run(gcnew SplashForm());
	}

	private: System::Void InterfaceForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		// creating and launching thread 'splashThread'
		Threading::Thread^ splashThread = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &InterfaceForm::splash));
		splashThread->Start();
		splashThread->Sleep(TimeSpan(0, 0, 3));


		// setting 'InterfaceForm' window
		chartAreaSetUp();
		drawParabola();
		drawPoints();

		this->generationQuantity = 1;
		this->generationIndex = 0;
		this->realizationAtBeginning = Visualization->RealizationPercentage;
		this->history = gcnew array<Chart^>(999);
		this->history[generationIndex] = Visualization;
		informationSetUp();


		// ending thread 'splashThread'
		splashThread->Abort();
		Application::OpenForms[0]->Activate();
	}


	// INTERNAL METHODS --------------------------------------------------------------------------------

	private: System::Void chartAreaSetUp() {
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisX->Minimum = this->Visualization->RangeStartArgument;
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisX->Maximum = this->Visualization->RangeEndArgument;
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisY->Minimum = System::Math::Round(this->Visualization->LowestChartValue / 100) * 100 - 50;
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisY->Maximum = System::Math::Round(this->Visualization->HighestChartValue / 100) * 100 + 50;
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisX->Interval = 2;
		this->chart_visualization->ChartAreas["ChartArea_visualization"]->AxisY->Interval = 10;
		// drawing axis
		this->chart_visualization->Series["Series_axisX"]->Points->AddXY(this->Visualization->RangeStartArgument, 0);
		this->chart_visualization->Series["Series_axisX"]->Points->AddXY(this->Visualization->RangeEndArgument, 0);
		this->chart_visualization->Series["Series_axisY"]->Points->AddXY(0, System::Math::Round(this->Visualization->LowestChartValue / 100) * 100 - 50);
		this->chart_visualization->Series["Series_axisY"]->Points->AddXY(0, System::Math::Round(this->Visualization->HighestChartValue / 100) * 100 + 50);
	}

	private: System::Void drawParabola() {
		for (int i = 0; i < 1280; i++) { // 1280 = 64 / 0.05
			this->chart_visualization->Series["Series_parabola"]->Points->AddXY(this->Visualization->Parabola[i]->X, this->Visualization->Parabola[i]->Y);
		}
	}

	private: System::Void drawPoints() {
		for (int i = 0; i <this->Visualization->InternalPopulation->InternalConfig->PopulationSize; i++) {
			this->chart_visualization->Series["Series_points"]->Points->AddXY(this->Visualization->Points[i]->X, this->Visualization->Points[i]->Y);
		}
	}

	private: System::Void informationSetUp() {
		// information labels setup
		this->label_genNum->Text = (this->generationIndex + 1).ToString("###");
		this->label_bestIndividual->Text = this->Visualization->BestIndividual.ToString("#0.00");
		this->label_target->Text = this->Visualization->TargetArgument.ToString("#0.00");
		this->label_average->Text = this->Visualization->AveragePointsValue.ToString("###0.00");
		this->label_targetValue->Text = this->Visualization->TargetValue.ToString("###0.00");
		this->label_realization->Text = this->Visualization->RealizationPercentage.ToString("#0.00");
		// setting target type sign
		if (this->Config->Flag_target == target::maximum) this->label_targetTypeSign->Text = "Maximum:";
		else if (this->Config->Flag_target == target::minimum) this->label_targetTypeSign->Text = "Minimum:";
		else if (this->Config->Flag_target == target::ekstremum) {
			if (this->Config->AFactor > 0) this->label_targetTypeSign->Text = "Minimum:";
			else this->label_targetTypeSign->Text = "Maximum:";
		}
		else throw gcnew System::ArgumentException("Invalid target (InterfaceForm.h|informationSetUp)");
		// progress bar setup
		if (this->Visualization->RealizationPercentage > this->realizationAtBeginning) {
			this->progressBar_realization->Value =
				static_cast<int>((this->Visualization->RealizationPercentage - this->realizationAtBeginning) * 100 / (100 - this->realizationAtBeginning));
		}
		else this->progressBar_realization->Value = 0;
	}

	// -------------------------------------------------------------------------------------------------


	// CONFIGURATION WINDOW OPENING --------------------------------------------------------------------

	private: System::Void button_configuration_Click(System::Object^  sender, System::EventArgs^  e) {
		
		// creating new configuration window
		ConfigurationForm^ ConfigurationWindow = gcnew ConfigurationForm();

		// adding external delegate to local 'ToSettings' event
		this->ToSettings += gcnew ToSettingsEventHandler(ConfigurationWindow, &ConfigurationForm::SetUp);
		// adding local delegate to external 'FromSettings' event
		ConfigurationWindow->FromSettings += gcnew FromSettingsEventHandler(this, &InterfaceForm::ApplyConfiguration);
		// adding local delegate to external 'WindowClosed' event
		ConfigurationWindow->WindowClosed += gcnew WindowClosedEventHandler(this, &InterfaceForm::EnableWindow);

		// running 'ToSettings' event
		this->ToSettings(this->Config);

		// showing configuration window
		ConfigurationWindow->Show();

		// blocking main window
		this->Enabled = false;
	}

	// -------------------------------------------------------------------------------------------------

			 
	// BUTTON CLICK EVENTS -----------------------------------------------------------------------------

	private: System::Void button_newGeneration_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->generationQuantity == 999) throw gcnew System::InvalidOperationException("Cannot create more than 999 generations");
		this->button_previous->Enabled = true;
		this->button_next->Enabled = false;
		this->Toolbox->evolve(Individuals);
		this->Visualization = gcnew Chart(Config, Individuals);
		this->chart_visualization->Series["Series_points"]->Points->Clear();
		drawPoints();
		this->generationQuantity++;
		this->generationIndex = this->generationQuantity - 1;
		this->history[generationIndex] = this->Visualization;
		informationSetUp();
		if (this->generationQuantity == 999) button_newGeneration->Enabled = false;
	}

	private: System::Void button_previous_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->generationIndex == this->generationQuantity - 1) this->button_next->Enabled = true;
		this->generationIndex--;
		this->Visualization = this->history[generationIndex];
		this->chart_visualization->Series["Series_points"]->Points->Clear();
		drawPoints();
		informationSetUp();
		if (this->generationIndex == 0) this->button_previous->Enabled = false;
	}

	private: System::Void button_next_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->generationIndex == 0) this->button_previous->Enabled = true;
		this->generationIndex++;
		this->Visualization = this->history[generationIndex];
		this->chart_visualization->Series["Series_points"]->Points->Clear();
		drawPoints();
		informationSetUp();
		if (this->generationIndex == this->generationQuantity - 1) this->button_next->Enabled = false;
	}

	private: System::Void button_restart_Click(System::Object^  sender, System::EventArgs^  e) {
		button_newGeneration->Enabled = true;
		this->Individuals = gcnew Population(Config);
		this->Visualization = gcnew Chart(Config, Individuals);
		this->history = gcnew array<Chart^>(999);
		this->generationQuantity = 1;
		this->generationIndex = 0;
		this->history[generationIndex] = this->Visualization;
		this->realizationAtBeginning = this->Visualization->RealizationPercentage;
		this->button_previous->Enabled = false;
		this->button_next->Enabled = false;
		this->chart_visualization->Series["Series_points"]->Points->Clear();
		drawPoints();
		informationSetUp();
	}

	private: System::Void button_quit_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
	}

	// -------------------------------------------------------------------------------------------------


	};
}