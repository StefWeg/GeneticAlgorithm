#pragma once

#include "GeneticAlgorythmEngine.h"


namespace GeneticAlgorythm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	// DELEGATE DECLARATION -------------------------------------------------------------------------------------

	// following delegate is needed for handling 'FromSettings' event (used in 'FROMSETTINGS EVENT' segment below)
	public delegate void FromSettingsEventHandler(Parameters^ passedConfig);
	// following delegate is needed for handling 'WindowClosed' event (used in 'WINDOWCLOSED EVENT' segment below)
	public delegate void WindowClosedEventHandler();
	// delegate is an object which stores information about how function should look like (accepted parameters and returned type)

	// ----------------------------------------------------------------------------------------------------------
	


	/// <summary>
	/// Summary for ConfigurationForm
	/// </summary>
	public ref class ConfigurationForm : public System::Windows::Forms::Form
	{


	// CONSTRUCTOR & DESTRUCTOR ---------------------------------------------------------------------------------

	public:
		ConfigurationForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->FromSettingsEventManager = nullptr;
			this->WindowClosedEventManager = nullptr;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ConfigurationForm()
		{
			if (components)
			{
				delete components;
			}
		}

	// ----------------------------------------------------------------------------------------------------------


	// FROMSETTINGS EVENT ---------------------------------------------------------------------------------------

	// creating event manager storing adressess to delegates
	private: FromSettingsEventHandler^ FromSettingsEventManager;

	// creating event FromSettings with required support methods
	public: event FromSettingsEventHandler^ FromSettings {
		void add(FromSettingsEventHandler^ del) { // adding new delegate to event manager associated with event
			this->FromSettingsEventManager = static_cast<FromSettingsEventHandler^>(Delegate::Combine(this->FromSettingsEventManager, del));
		}
		void remove(FromSettingsEventHandler^ del) { // removing delegate from event manager associated with event
			this->FromSettingsEventManager = static_cast<FromSettingsEventHandler^>(Delegate::Remove(this->FromSettingsEventManager, del));
		}
		void raise(Parameters^ passedConfig) { // runs delegate functions using passed argument
			if (this->FromSettingsEventManager != nullptr) {
				this->FromSettingsEventManager->Invoke(passedConfig);
			}
		}
	} // event used in 'button_apply_Click' method below ('RETURN TO MAIN WINDOW WITH APPLY BUTTON' segment)

	// ----------------------------------------------------------------------------------------------------------


	// WINDOWCLOSED EVENT ---------------------------------------------------------------------------------------

	// creating event manager storing adressess to delegates
	private: WindowClosedEventHandler^ WindowClosedEventManager;

			 // creating event FromSettings with required support methods
	public: event WindowClosedEventHandler^ WindowClosed {
		void add(WindowClosedEventHandler^ del) { // adding new delegate to event manager associated with event
			this->WindowClosedEventManager = static_cast<WindowClosedEventHandler^>(Delegate::Combine(this->WindowClosedEventManager, del));
		}
		void remove(WindowClosedEventHandler^ del) { // removing delegate from event manager associated with event
			this->WindowClosedEventManager = static_cast<WindowClosedEventHandler^>(Delegate::Remove(this->WindowClosedEventManager, del));
		}
		void raise() { // runs delegate functions using passed arguments
			if (this->WindowClosedEventManager != nullptr) {
				this->WindowClosedEventManager->Invoke();
			}
		}
	} // event used in 'ConfigurationForm_FormClosed' method below ('WINDOW CLOSED EVENT' segment)

	// ----------------------------------------------------------------------------------------------------------
	  

	// PUBLIC SETUP METHOD --------------------------------------------------------------------------------------

	// 'SetUp' function is delegate of the 'ToSettings' event from 'InterfaceForm.h'
	public: void SetUp(Parameters^ passedConfig) {

		// setting aFactor, bFactor & cFactor
		this->numericUpDown_aFactor->Value = Convert::ToDecimal(passedConfig->AFactor);
		if (this->numericUpDown_aFactor->Value == Convert::ToDecimal(0.1)) {
			this->previousAFactorWasPositive01 = true;
			this->previousAFactorWasNegative01 = false;
		}
		else if (this->numericUpDown_aFactor->Value == Convert::ToDecimal(-0.1)) {
			this->previousAFactorWasNegative01 = true;
			this->previousAFactorWasPositive01 = false;
		}
		else if (this->numericUpDown_aFactor->Value == 0) {
			throw gcnew System::ArgumentException("Invalid aFactor (ConfigurationForm.h|SetUp)");
		}
		else {
			this->previousAFactorWasPositive01 = false;
			this->previousAFactorWasNegative01 = false;
		}
		this->numericUpDown_bFactor->Value = Convert::ToDecimal(passedConfig->BFactor);
		this->numericUpDown_cFactor->Value = Convert::ToDecimal(passedConfig->CFactor);

		// setting population size
		switch (passedConfig->PopulationSize) {
		case 10:
			this->comboBox_populationSize->SelectedItem = "10";
			break;
		case 20:
			this->comboBox_populationSize->SelectedItem = "20";
			break;
		case 50:
			this->comboBox_populationSize->SelectedItem = "50";
			break;
		case 100:
			this->comboBox_populationSize->SelectedItem = "100";
			break;
		case 200:
			this->comboBox_populationSize->SelectedItem = "200";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid population size (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting coding method
		switch (passedConfig->Flag_codingMethod) {
		case codingMethod::binary8:
			this->comboBox_codingMethod->SelectedItem = "binary8";
			break;
		case codingMethod::binary10:
			this->comboBox_codingMethod->SelectedItem = "binary10";
			break;
		case codingMethod::integers:
			this->comboBox_codingMethod->SelectedItem = "integers";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid coding method (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting target
		switch (passedConfig->Flag_target) {
		case target::maximum:
			this->comboBox_target->SelectedItem = "maximum";
			break;
		case target::minimum:
			this->comboBox_target->SelectedItem = "minimum";
			break;
		case target::ekstremum:
			this->comboBox_target->SelectedItem = "ekstremum";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid target (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting fitness function type
		switch (passedConfig->Flag_fitnessFunctionType) {
		case fitnessFunctionType::linear:
			this->comboBox_fitnessFunctionType->SelectedItem = "linear";
			break;
		case fitnessFunctionType::exponential:
			this->comboBox_fitnessFunctionType->SelectedItem = "exponential";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid fitness function type (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting selection method
		switch (passedConfig->Flag_selectionMethod) {
		case selectionMethod::roulette:
			this->comboBox_selectionMethod->SelectedItem = "roulette";
			break;
		case selectionMethod::ranking:
			this->comboBox_selectionMethod->SelectedItem = "ranking";
			break;
		case selectionMethod::tournament:
			this->comboBox_selectionMethod->SelectedItem = "tournament";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid selection method (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting selection modification
		switch (passedConfig->Flag_selectionModification) {
		case selectionModification::none:
			this->comboBox_selectionModification->SelectedItem = "none";
			break;
		case selectionModification::eliteSelection:
			this->comboBox_selectionModification->SelectedItem = "elite selection";
			break;
		case selectionModification::partialExchange:
			this->comboBox_selectionModification->SelectedItem = "partial exchange";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid selection modification (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting crossover method
		switch (passedConfig->Flag_crossoverMethod) {
		case crossoverMethod::onePointCrossover:
			this->comboBox_crossoverMethod->SelectedItem = "one point crossover";
			break;
		case crossoverMethod::twoPointCrossover:
			this->comboBox_crossoverMethod->SelectedItem = "two point crossover";
			break;
		case crossoverMethod::uniformCrossover:
			this->comboBox_crossoverMethod->SelectedItem = "uniform crossover";
			break;
		case crossoverMethod::averaging:
			this->comboBox_crossoverMethod->SelectedItem = "averaging";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid crossover method (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting crossover probability
		numericUpDown_crossoverProbability->Value = Convert::ToDecimal(passedConfig->CrossoverProbability);

		// setting mutation method
		switch (passedConfig->Flag_mutationMethod) {
		case mutationMethod::none:
			this->comboBox_mutationMethod->SelectedItem = "none";
			break;
		case mutationMethod::geneNegation:
			this->comboBox_mutationMethod->SelectedItem = "gene negation";
			break;
		case mutationMethod::geneSwap:
			this->comboBox_mutationMethod->SelectedItem = "gene swap";
			break;
		case mutationMethod::permutation:
			this->comboBox_mutationMethod->SelectedItem = "permutation";
			break;
		default:
			throw gcnew System::ArgumentException("Invalid mutation method (ConfigurationForm.h|SetUp)");
			break;
		}

		// setting mutation probability
		this->numericUpDown_mutationProbability->Value = Convert::ToDecimal(passedConfig->MutationProbability);

	}

	// ----------------------------------------------------------------------------------------------------------


	// INTERFACE CONTROLS DECLARATIONS --------------------------------------------------------------------------


	private: System::Windows::Forms::GroupBox^  groupBox_parabola;
	private: System::Windows::Forms::Label^  label_equation1;
	private: System::Windows::Forms::Label^  label_equation4;
	private: System::Windows::Forms::Label^  label_equation2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_aFactor;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_bFactor;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_cFactor;
	private: System::Windows::Forms::Label^  label_equation3;
	private: System::Windows::Forms::GroupBox^  groupBox_populationSize;
	private: System::Windows::Forms::ComboBox^  comboBox_populationSize;
	private: System::Windows::Forms::GroupBox^  groupBox_recombinationProbability;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_crossoverProbability;
	private: System::Windows::Forms::GroupBox^  groupBox_mutationProbability;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_mutationProbability;
	private: System::Windows::Forms::Button^  button_apply;
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::Panel^  panel_configuration;
	private: System::Windows::Forms::ComboBox^  comboBox_codingMethod;
	private: System::Windows::Forms::GroupBox^  groupBox_codingMethod;
	private: System::Windows::Forms::GroupBox^  groupBox_target;
	private: System::Windows::Forms::ComboBox^  comboBox_target;
	private: System::Windows::Forms::GroupBox^  groupBox_selectionMethod;
	private: System::Windows::Forms::ComboBox^  comboBox_selectionMethod;
	private: System::Windows::Forms::GroupBox^  groupBox_fitnessFunctionType;
	private: System::Windows::Forms::ComboBox^  comboBox_fitnessFunctionType;
	private: System::Windows::Forms::GroupBox^  groupBox_crossoverMethod;
	private: System::Windows::Forms::ComboBox^  comboBox_crossoverMethod;
	private: System::Windows::Forms::GroupBox^  groupBox_selectionModification;
	private: System::Windows::Forms::ComboBox^  comboBox_selectionModification;
	private: System::Windows::Forms::GroupBox^  groupBox_mutationMethod;
	private: System::Windows::Forms::ComboBox^  comboBox_mutationMethod;
	private: System::Windows::Forms::Button^  button_defaultSettings;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	// ----------------------------------------------------------------------------------------------------------


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox_codingMethod = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_codingMethod = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox_target = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_target = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_selectionMethod = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_selectionMethod = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_fitnessFunctionType = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_fitnessFunctionType = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_crossoverMethod = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_crossoverMethod = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_selectionModification = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_selectionModification = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_mutationMethod = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_mutationMethod = (gcnew System::Windows::Forms::ComboBox());
			this->button_defaultSettings = (gcnew System::Windows::Forms::Button());
			this->groupBox_parabola = (gcnew System::Windows::Forms::GroupBox());
			this->label_equation1 = (gcnew System::Windows::Forms::Label());
			this->label_equation4 = (gcnew System::Windows::Forms::Label());
			this->label_equation2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_aFactor = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown_bFactor = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown_cFactor = (gcnew System::Windows::Forms::NumericUpDown());
			this->label_equation3 = (gcnew System::Windows::Forms::Label());
			this->groupBox_populationSize = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_populationSize = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_recombinationProbability = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown_crossoverProbability = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox_mutationProbability = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown_mutationProbability = (gcnew System::Windows::Forms::NumericUpDown());
			this->button_apply = (gcnew System::Windows::Forms::Button());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->panel_configuration = (gcnew System::Windows::Forms::Panel());
			this->groupBox_codingMethod->SuspendLayout();
			this->groupBox_target->SuspendLayout();
			this->groupBox_selectionMethod->SuspendLayout();
			this->groupBox_fitnessFunctionType->SuspendLayout();
			this->groupBox_crossoverMethod->SuspendLayout();
			this->groupBox_selectionModification->SuspendLayout();
			this->groupBox_mutationMethod->SuspendLayout();
			this->groupBox_parabola->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_aFactor))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_bFactor))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_cFactor))->BeginInit();
			this->groupBox_populationSize->SuspendLayout();
			this->groupBox_recombinationProbability->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_crossoverProbability))->BeginInit();
			this->groupBox_mutationProbability->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_mutationProbability))->BeginInit();
			this->panel_configuration->SuspendLayout();
			this->SuspendLayout();
			// 
			// comboBox_codingMethod
			// 
			this->comboBox_codingMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_codingMethod->FormattingEnabled = true;
			this->comboBox_codingMethod->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->comboBox_codingMethod->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"binary8", L"binary10", L"integers" });
			this->comboBox_codingMethod->Location = System::Drawing::Point(10, 20);
			this->comboBox_codingMethod->Name = L"comboBox_codingMethod";
			this->comboBox_codingMethod->Size = System::Drawing::Size(120, 21);
			this->comboBox_codingMethod->TabIndex = 0;
			this->comboBox_codingMethod->SelectedIndexChanged += gcnew System::EventHandler(this, &ConfigurationForm::comboBox_codingMethod_SelectedIndexChanged);
			// 
			// groupBox_codingMethod
			// 
			this->groupBox_codingMethod->Controls->Add(this->comboBox_codingMethod);
			this->groupBox_codingMethod->Location = System::Drawing::Point(10, 70);
			this->groupBox_codingMethod->Name = L"groupBox_codingMethod";
			this->groupBox_codingMethod->Size = System::Drawing::Size(140, 51);
			this->groupBox_codingMethod->TabIndex = 6;
			this->groupBox_codingMethod->TabStop = false;
			this->groupBox_codingMethod->Text = L"Coding method";
			// 
			// groupBox_target
			// 
			this->groupBox_target->Controls->Add(this->comboBox_target);
			this->groupBox_target->Location = System::Drawing::Point(10, 130);
			this->groupBox_target->Name = L"groupBox_target";
			this->groupBox_target->Size = System::Drawing::Size(140, 51);
			this->groupBox_target->TabIndex = 7;
			this->groupBox_target->TabStop = false;
			this->groupBox_target->Text = L"Target";
			// 
			// comboBox_target
			// 
			this->comboBox_target->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_target->FormattingEnabled = true;
			this->comboBox_target->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"maximum", L"minimum", L"ekstremum" });
			this->comboBox_target->Location = System::Drawing::Point(10, 20);
			this->comboBox_target->Name = L"comboBox_target";
			this->comboBox_target->Size = System::Drawing::Size(120, 21);
			this->comboBox_target->TabIndex = 0;
			// 
			// groupBox_selectionMethod
			// 
			this->groupBox_selectionMethod->Controls->Add(this->comboBox_selectionMethod);
			this->groupBox_selectionMethod->Location = System::Drawing::Point(175, 70);
			this->groupBox_selectionMethod->Name = L"groupBox_selectionMethod";
			this->groupBox_selectionMethod->Size = System::Drawing::Size(140, 51);
			this->groupBox_selectionMethod->TabIndex = 9;
			this->groupBox_selectionMethod->TabStop = false;
			this->groupBox_selectionMethod->Text = L"Selection method";
			// 
			// comboBox_selectionMethod
			// 
			this->comboBox_selectionMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_selectionMethod->FormattingEnabled = true;
			this->comboBox_selectionMethod->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"roulette", L"ranking", L"tournament" });
			this->comboBox_selectionMethod->Location = System::Drawing::Point(10, 20);
			this->comboBox_selectionMethod->Name = L"comboBox_selectionMethod";
			this->comboBox_selectionMethod->Size = System::Drawing::Size(120, 21);
			this->comboBox_selectionMethod->TabIndex = 0;
			// 
			// groupBox_fitnessFunctionType
			// 
			this->groupBox_fitnessFunctionType->Controls->Add(this->comboBox_fitnessFunctionType);
			this->groupBox_fitnessFunctionType->Location = System::Drawing::Point(10, 190);
			this->groupBox_fitnessFunctionType->Name = L"groupBox_fitnessFunctionType";
			this->groupBox_fitnessFunctionType->Size = System::Drawing::Size(140, 51);
			this->groupBox_fitnessFunctionType->TabIndex = 8;
			this->groupBox_fitnessFunctionType->TabStop = false;
			this->groupBox_fitnessFunctionType->Text = L"Fitness function type";
			// 
			// comboBox_fitnessFunctionType
			// 
			this->comboBox_fitnessFunctionType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_fitnessFunctionType->FormattingEnabled = true;
			this->comboBox_fitnessFunctionType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"linear", L"exponential" });
			this->comboBox_fitnessFunctionType->Location = System::Drawing::Point(10, 20);
			this->comboBox_fitnessFunctionType->Name = L"comboBox_fitnessFunctionType";
			this->comboBox_fitnessFunctionType->Size = System::Drawing::Size(120, 21);
			this->comboBox_fitnessFunctionType->TabIndex = 0;
			// 
			// groupBox_crossoverMethod
			// 
			this->groupBox_crossoverMethod->Controls->Add(this->comboBox_crossoverMethod);
			this->groupBox_crossoverMethod->Location = System::Drawing::Point(175, 130);
			this->groupBox_crossoverMethod->Name = L"groupBox_crossoverMethod";
			this->groupBox_crossoverMethod->Size = System::Drawing::Size(140, 51);
			this->groupBox_crossoverMethod->TabIndex = 11;
			this->groupBox_crossoverMethod->TabStop = false;
			this->groupBox_crossoverMethod->Text = L"Crossover method";
			// 
			// comboBox_crossoverMethod
			// 
			this->comboBox_crossoverMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_crossoverMethod->FormattingEnabled = true;
			this->comboBox_crossoverMethod->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"one point crossover", L"two point crossover",
					L"uniform crossover", L"averaging"
			});
			this->comboBox_crossoverMethod->Location = System::Drawing::Point(10, 20);
			this->comboBox_crossoverMethod->Name = L"comboBox_crossoverMethod";
			this->comboBox_crossoverMethod->Size = System::Drawing::Size(120, 21);
			this->comboBox_crossoverMethod->TabIndex = 0;
			// 
			// groupBox_selectionModification
			// 
			this->groupBox_selectionModification->Controls->Add(this->comboBox_selectionModification);
			this->groupBox_selectionModification->Location = System::Drawing::Point(320, 70);
			this->groupBox_selectionModification->Name = L"groupBox_selectionModification";
			this->groupBox_selectionModification->Size = System::Drawing::Size(140, 51);
			this->groupBox_selectionModification->TabIndex = 10;
			this->groupBox_selectionModification->TabStop = false;
			this->groupBox_selectionModification->Text = L"Selection modification";
			// 
			// comboBox_selectionModification
			// 
			this->comboBox_selectionModification->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_selectionModification->FormattingEnabled = true;
			this->comboBox_selectionModification->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"none", L"elite selection",
					L"partial exchange"
			});
			this->comboBox_selectionModification->Location = System::Drawing::Point(10, 20);
			this->comboBox_selectionModification->Name = L"comboBox_selectionModification";
			this->comboBox_selectionModification->Size = System::Drawing::Size(120, 21);
			this->comboBox_selectionModification->TabIndex = 0;
			// 
			// groupBox_mutationMethod
			// 
			this->groupBox_mutationMethod->Controls->Add(this->comboBox_mutationMethod);
			this->groupBox_mutationMethod->Location = System::Drawing::Point(175, 190);
			this->groupBox_mutationMethod->Name = L"groupBox_mutationMethod";
			this->groupBox_mutationMethod->Size = System::Drawing::Size(140, 51);
			this->groupBox_mutationMethod->TabIndex = 13;
			this->groupBox_mutationMethod->TabStop = false;
			this->groupBox_mutationMethod->Text = L"Mutation method";
			// 
			// comboBox_mutationMethod
			// 
			this->comboBox_mutationMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_mutationMethod->FormattingEnabled = true;
			this->comboBox_mutationMethod->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"none", L"gene negation", L"gene swap",
					L"permutation"
			});
			this->comboBox_mutationMethod->Location = System::Drawing::Point(10, 20);
			this->comboBox_mutationMethod->Name = L"comboBox_mutationMethod";
			this->comboBox_mutationMethod->Size = System::Drawing::Size(120, 21);
			this->comboBox_mutationMethod->TabIndex = 0;
			this->comboBox_mutationMethod->SelectedIndexChanged += gcnew System::EventHandler(this, &ConfigurationForm::comboBox_mutationMethod_SelectedIndexChanged);
			// 
			// button_defaultSettings
			// 
			this->button_defaultSettings->Location = System::Drawing::Point(20, 260);
			this->button_defaultSettings->Name = L"button_defaultSettings";
			this->button_defaultSettings->Size = System::Drawing::Size(120, 30);
			this->button_defaultSettings->TabIndex = 15;
			this->button_defaultSettings->Text = L"Default settings";
			this->button_defaultSettings->UseVisualStyleBackColor = true;
			this->button_defaultSettings->Click += gcnew System::EventHandler(this, &ConfigurationForm::button_defaultSettings_Click);
			// 
			// groupBox_parabola
			// 
			this->groupBox_parabola->Controls->Add(this->label_equation1);
			this->groupBox_parabola->Controls->Add(this->label_equation4);
			this->groupBox_parabola->Controls->Add(this->label_equation2);
			this->groupBox_parabola->Location = System::Drawing::Point(10, 10);
			this->groupBox_parabola->Name = L"groupBox_parabola";
			this->groupBox_parabola->Size = System::Drawing::Size(305, 51);
			this->groupBox_parabola->TabIndex = 1;
			this->groupBox_parabola->TabStop = false;
			this->groupBox_parabola->Text = L"Parabola";
			// 
			// label_equation1
			// 
			this->label_equation1->AutoSize = true;
			this->label_equation1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_equation1->Location = System::Drawing::Point(8, 22);
			this->label_equation1->Name = L"label_equation1";
			this->label_equation1->Size = System::Drawing::Size(33, 13);
			this->label_equation1->TabIndex = 0;
			this->label_equation1->Text = L"f(x)  =";
			// 
			// label_equation4
			// 
			this->label_equation4->AutoSize = true;
			this->label_equation4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_equation4->Location = System::Drawing::Point(205, 22);
			this->label_equation4->Name = L"label_equation4";
			this->label_equation4->Size = System::Drawing::Size(27, 13);
			this->label_equation4->TabIndex = 0;
			this->label_equation4->Text = L"x   +";
			// 
			// label_equation2
			// 
			this->label_equation2->AutoSize = true;
			this->label_equation2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_equation2->Location = System::Drawing::Point(104, 22);
			this->label_equation2->Name = L"label_equation2";
			this->label_equation2->Size = System::Drawing::Size(36, 13);
			this->label_equation2->TabIndex = 0;
			this->label_equation2->Text = L"x      +";
			// 
			// numericUpDown_aFactor
			// 
			this->numericUpDown_aFactor->DecimalPlaces = 1;
			this->numericUpDown_aFactor->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->numericUpDown_aFactor->Location = System::Drawing::Point(57, 30);
			this->numericUpDown_aFactor->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown_aFactor->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->numericUpDown_aFactor->Name = L"numericUpDown_aFactor";
			this->numericUpDown_aFactor->Size = System::Drawing::Size(55, 20);
			this->numericUpDown_aFactor->TabIndex = 2;
			this->numericUpDown_aFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->numericUpDown_aFactor->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, -2147418112 });
			this->numericUpDown_aFactor->ValueChanged += gcnew System::EventHandler(this, &ConfigurationForm::numericUpDown_aFactor_ValueChanged);
			// 
			// numericUpDown_bFactor
			// 
			this->numericUpDown_bFactor->DecimalPlaces = 1;
			this->numericUpDown_bFactor->Location = System::Drawing::Point(158, 30);
			this->numericUpDown_bFactor->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUpDown_bFactor->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, System::Int32::MinValue });
			this->numericUpDown_bFactor->Name = L"numericUpDown_bFactor";
			this->numericUpDown_bFactor->Size = System::Drawing::Size(55, 20);
			this->numericUpDown_bFactor->TabIndex = 3;
			this->numericUpDown_bFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->numericUpDown_bFactor->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// numericUpDown_cFactor
			// 
			this->numericUpDown_cFactor->DecimalPlaces = 1;
			this->numericUpDown_cFactor->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUpDown_cFactor->Location = System::Drawing::Point(248, 30);
			this->numericUpDown_cFactor->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numericUpDown_cFactor->Name = L"numericUpDown_cFactor";
			this->numericUpDown_cFactor->Size = System::Drawing::Size(55, 20);
			this->numericUpDown_cFactor->TabIndex = 4;
			this->numericUpDown_cFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->numericUpDown_cFactor->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// label_equation3
			// 
			this->label_equation3->AutoSize = true;
			this->label_equation3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_equation3->Location = System::Drawing::Point(122, 26);
			this->label_equation3->Name = L"label_equation3";
			this->label_equation3->Size = System::Drawing::Size(10, 12);
			this->label_equation3->TabIndex = 0;
			this->label_equation3->Text = L"2";
			// 
			// groupBox_populationSize
			// 
			this->groupBox_populationSize->Controls->Add(this->comboBox_populationSize);
			this->groupBox_populationSize->Location = System::Drawing::Point(320, 10);
			this->groupBox_populationSize->Name = L"groupBox_populationSize";
			this->groupBox_populationSize->Size = System::Drawing::Size(140, 51);
			this->groupBox_populationSize->TabIndex = 5;
			this->groupBox_populationSize->TabStop = false;
			this->groupBox_populationSize->Text = L"Population size";
			// 
			// comboBox_populationSize
			// 
			this->comboBox_populationSize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_populationSize->FormattingEnabled = true;
			this->comboBox_populationSize->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"10", L"20", L"50", L"100", L"200" });
			this->comboBox_populationSize->Location = System::Drawing::Point(10, 20);
			this->comboBox_populationSize->Name = L"comboBox_populationSize";
			this->comboBox_populationSize->Size = System::Drawing::Size(120, 21);
			this->comboBox_populationSize->TabIndex = 0;
			// 
			// groupBox_recombinationProbability
			// 
			this->groupBox_recombinationProbability->Controls->Add(this->numericUpDown_crossoverProbability);
			this->groupBox_recombinationProbability->Location = System::Drawing::Point(320, 130);
			this->groupBox_recombinationProbability->Name = L"groupBox_recombinationProbability";
			this->groupBox_recombinationProbability->Size = System::Drawing::Size(140, 51);
			this->groupBox_recombinationProbability->TabIndex = 12;
			this->groupBox_recombinationProbability->TabStop = false;
			this->groupBox_recombinationProbability->Text = L"Crossover probability %";
			// 
			// numericUpDown_crossoverProbability
			// 
			this->numericUpDown_crossoverProbability->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numericUpDown_crossoverProbability->Location = System::Drawing::Point(10, 20);
			this->numericUpDown_crossoverProbability->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->numericUpDown_crossoverProbability->Name = L"numericUpDown_crossoverProbability";
			this->numericUpDown_crossoverProbability->Size = System::Drawing::Size(120, 20);
			this->numericUpDown_crossoverProbability->TabIndex = 0;
			this->numericUpDown_crossoverProbability->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numericUpDown_crossoverProbability->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 80, 0, 0, 0 });
			// 
			// groupBox_mutationProbability
			// 
			this->groupBox_mutationProbability->Controls->Add(this->numericUpDown_mutationProbability);
			this->groupBox_mutationProbability->Location = System::Drawing::Point(320, 190);
			this->groupBox_mutationProbability->Name = L"groupBox_mutationProbability";
			this->groupBox_mutationProbability->Size = System::Drawing::Size(140, 51);
			this->groupBox_mutationProbability->TabIndex = 14;
			this->groupBox_mutationProbability->TabStop = false;
			this->groupBox_mutationProbability->Text = L"Mutation probability %";
			// 
			// numericUpDown_mutationProbability
			// 
			this->numericUpDown_mutationProbability->Location = System::Drawing::Point(10, 20);
			this->numericUpDown_mutationProbability->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUpDown_mutationProbability->Name = L"numericUpDown_mutationProbability";
			this->numericUpDown_mutationProbability->Size = System::Drawing::Size(120, 20);
			this->numericUpDown_mutationProbability->TabIndex = 0;
			this->numericUpDown_mutationProbability->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button_apply
			// 
			this->button_apply->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->button_apply->Location = System::Drawing::Point(210, 260);
			this->button_apply->Name = L"button_apply";
			this->button_apply->Size = System::Drawing::Size(120, 30);
			this->button_apply->TabIndex = 16;
			this->button_apply->Text = L"Apply";
			this->button_apply->UseVisualStyleBackColor = true;
			this->button_apply->Click += gcnew System::EventHandler(this, &ConfigurationForm::button_apply_Click);
			// 
			// button_cancel
			// 
			this->button_cancel->Location = System::Drawing::Point(340, 260);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(120, 30);
			this->button_cancel->TabIndex = 17;
			this->button_cancel->Text = L"Cancel";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->Click += gcnew System::EventHandler(this, &ConfigurationForm::button_cancel_Click);
			// 
			// panel_configuration
			// 
			this->panel_configuration->Controls->Add(this->button_defaultSettings);
			this->panel_configuration->Controls->Add(this->button_cancel);
			this->panel_configuration->Controls->Add(this->groupBox_mutationMethod);
			this->panel_configuration->Controls->Add(this->button_apply);
			this->panel_configuration->Controls->Add(this->groupBox_fitnessFunctionType);
			this->panel_configuration->Controls->Add(this->groupBox_crossoverMethod);
			this->panel_configuration->Controls->Add(this->groupBox_target);
			this->panel_configuration->Controls->Add(this->groupBox_mutationProbability);
			this->panel_configuration->Controls->Add(this->groupBox_selectionModification);
			this->panel_configuration->Controls->Add(this->groupBox_recombinationProbability);
			this->panel_configuration->Controls->Add(this->groupBox_selectionMethod);
			this->panel_configuration->Controls->Add(this->groupBox_populationSize);
			this->panel_configuration->Controls->Add(this->label_equation3);
			this->panel_configuration->Controls->Add(this->numericUpDown_cFactor);
			this->panel_configuration->Controls->Add(this->groupBox_codingMethod);
			this->panel_configuration->Controls->Add(this->numericUpDown_bFactor);
			this->panel_configuration->Controls->Add(this->numericUpDown_aFactor);
			this->panel_configuration->Controls->Add(this->groupBox_parabola);
			this->panel_configuration->Location = System::Drawing::Point(0, 0);
			this->panel_configuration->Name = L"panel_configuration";
			this->panel_configuration->Size = System::Drawing::Size(470, 300);
			this->panel_configuration->TabIndex = 0;
			// 
			// ConfigurationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 300);
			this->Controls->Add(this->panel_configuration);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(486, 339);
			this->MinimumSize = System::Drawing::Size(486, 339);
			this->Name = L"ConfigurationForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Configuration";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ConfigurationForm::ConfigurationForm_FormClosed);
			this->groupBox_codingMethod->ResumeLayout(false);
			this->groupBox_target->ResumeLayout(false);
			this->groupBox_selectionMethod->ResumeLayout(false);
			this->groupBox_fitnessFunctionType->ResumeLayout(false);
			this->groupBox_crossoverMethod->ResumeLayout(false);
			this->groupBox_selectionModification->ResumeLayout(false);
			this->groupBox_mutationMethod->ResumeLayout(false);
			this->groupBox_parabola->ResumeLayout(false);
			this->groupBox_parabola->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_aFactor))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_bFactor))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_cFactor))->EndInit();
			this->groupBox_populationSize->ResumeLayout(false);
			this->groupBox_recombinationProbability->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_crossoverProbability))->EndInit();
			this->groupBox_mutationProbability->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_mutationProbability))->EndInit();
			this->panel_configuration->ResumeLayout(false);
			this->panel_configuration->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	// RETURN TO MAIN WINDOW WITH APPLY BUTTON ------------------------------------------------------------------

	private: System::Void button_apply_Click(System::Object^  sender, System::EventArgs^  e) {

		Parameters^ configToApply = gcnew Parameters();

		// setting aFactor, bFactor & cFactor
		configToApply->AFactor = static_cast<double>(numericUpDown_aFactor->Value);
		configToApply->BFactor = static_cast<double>(numericUpDown_bFactor->Value);
		configToApply->CFactor = static_cast<double>(numericUpDown_cFactor->Value);

		// setting population size
		System::String^ chosenPopulationSize = gcnew System::String(comboBox_populationSize->Text);
		if (chosenPopulationSize->Equals("10")) configToApply->PopulationSize = 10;
		else if (chosenPopulationSize->Equals("20")) configToApply->PopulationSize = 20;
		else if (chosenPopulationSize->Equals("50")) configToApply->PopulationSize = 50;
		else if (chosenPopulationSize->Equals("100")) configToApply->PopulationSize = 100;
		else if (chosenPopulationSize->Equals("200")) configToApply->PopulationSize = 200;
		else throw gcnew System::ArgumentException("Invalid population size (ConfigurationForm.h|button_apply_Click)");

		// setting coding method
		System::String^ chosenCodingMethod = gcnew System::String(comboBox_codingMethod->Text);
		if (chosenCodingMethod->Equals("binary8")) configToApply->Flag_codingMethod = codingMethod::binary8;
		else if (chosenCodingMethod->Equals("binary10")) configToApply->Flag_codingMethod = codingMethod::binary10;
		else if (chosenCodingMethod->Equals("integers")) configToApply->Flag_codingMethod = codingMethod::integers;
		else throw gcnew System::ArgumentException("Invalid coding method (ConfigurationForm.h|button_apply_Click)");

		// setting target
		System::String^ chosenTarget = gcnew System::String(comboBox_target->Text);
		if (chosenTarget->Equals("maximum")) configToApply->Flag_target = target::maximum;
		else if (chosenTarget->Equals("minimum")) configToApply->Flag_target = target::minimum;
		else if (chosenTarget->Equals("ekstremum")) configToApply->Flag_target = target::ekstremum;
		else throw gcnew System::ArgumentException("Invalid target (ConfigurationForm.h|button_apply_Click)");

		// setting fitness function type
		System::String^ chosenFitnessFunctionType = gcnew System::String(comboBox_fitnessFunctionType->Text);
		if (chosenFitnessFunctionType->Equals("linear")) configToApply->Flag_fitnessFunctionType = fitnessFunctionType::linear;
		else if (chosenFitnessFunctionType->Equals("exponential")) configToApply->Flag_fitnessFunctionType = fitnessFunctionType::exponential;
		else throw gcnew System::ArgumentException("Invalid fitness funtion type (ConfigurationForm.h|button_apply_Click)");

		// setting selection method
		System::String^ chosenSelectionMethod = gcnew System::String(comboBox_selectionMethod->Text);
		if (chosenSelectionMethod->Equals("roulette")) configToApply->Flag_selectionMethod = selectionMethod::roulette;
		else if (chosenSelectionMethod->Equals("ranking")) configToApply->Flag_selectionMethod = selectionMethod::ranking;
		else if (chosenSelectionMethod->Equals("tournament")) configToApply->Flag_selectionMethod = selectionMethod::tournament;
		else throw gcnew System::ArgumentException("Invalid selection method (ConfigurationForm.h|button_apply_Click)");

		// setting selection modification
		System::String^ chosenSelectionModification = gcnew System::String(comboBox_selectionModification->Text);
		if (chosenSelectionModification->Equals("none")) configToApply->Flag_selectionModification = selectionModification::none;
		else if (chosenSelectionModification->Equals("elite selection")) configToApply->Flag_selectionModification = selectionModification::eliteSelection;
		else if (chosenSelectionModification->Equals("partial exchange")) configToApply->Flag_selectionModification = selectionModification::partialExchange;
		else throw gcnew System::ArgumentException("Invalid selection modification (ConfigurationForm.h|button_apply_Click)");

		// setting crossover method
		System::String^ chosenCrossoverMethod = gcnew System::String(comboBox_crossoverMethod->Text);
		if (chosenCrossoverMethod->Equals("one point crossover")) configToApply->Flag_crossoverMethod = crossoverMethod::onePointCrossover;
		else if (chosenCrossoverMethod->Equals("two point crossover")) configToApply->Flag_crossoverMethod = crossoverMethod::twoPointCrossover;
		else if (chosenCrossoverMethod->Equals("uniform crossover")) configToApply->Flag_crossoverMethod = crossoverMethod::uniformCrossover;
		else if (chosenCrossoverMethod->Equals("averaging")) configToApply->Flag_crossoverMethod = crossoverMethod::averaging;
		else throw gcnew System::ArgumentException("Invalid crossover method (ConfigurationForm.h|button_apply_Click)");

		// setting crossover probability
		configToApply->CrossoverProbability = static_cast<int>(numericUpDown_crossoverProbability->Value);

		// setting mutation method
		System::String^ chosenMutationMethod = gcnew System::String(comboBox_mutationMethod->Text);
		if (chosenMutationMethod->Equals("none")) configToApply->Flag_mutationMethod = mutationMethod::none;
		else if (chosenMutationMethod->Equals("gene negation")) configToApply->Flag_mutationMethod = mutationMethod::geneNegation;
		else if (chosenMutationMethod->Equals("gene swap")) configToApply->Flag_mutationMethod = mutationMethod::geneSwap;
		else if (chosenMutationMethod->Equals("permutation")) configToApply->Flag_mutationMethod = mutationMethod::permutation;
		else throw gcnew System::ArgumentException("Invalid mutation method (ConfigurationForm.h|button_apply_Click)");

		// setting mutation probability
		configToApply->MutationProbability = static_cast<int>(numericUpDown_mutationProbability->Value);

		// raising event with argument
		this->FromSettings(configToApply);

		// closing configuration window
		ConfigurationForm::Close();
	}

	// ----------------------------------------------------------------------------------------------------------


	// WINDOW CLOSED EVENT --------------------------------------------------------------------------------------

	private: System::Void ConfigurationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
	{
		this->WindowClosed();
	}

	// ----------------------------------------------------------------------------------------------------------


	// BUTTON CLICK EVENTS --------------------------------------------------------------------------------------

	private: System::Void button_defaultSettings_Click(System::Object^  sender, System::EventArgs^  e) {

		this->numericUpDown_aFactor->Value = Convert::ToDecimal(-0.1);
		this->previousAFactorWasPositive01 = false;
		this->previousAFactorWasNegative01 = true;
		this->numericUpDown_bFactor->Value = 1;
		this->numericUpDown_cFactor->Value = 10;
		this->comboBox_populationSize->SelectedItem = "10";
		this->comboBox_codingMethod->SelectedItem = "binary8";
		this->comboBox_target->SelectedItem = "maximum";
		this->comboBox_fitnessFunctionType->SelectedItem = "linear";
		this->comboBox_selectionMethod->SelectedItem = "roulette";
		this->comboBox_selectionModification->SelectedItem = "none";
		this->comboBox_crossoverMethod->SelectedItem = "one point crossover";
		this->numericUpDown_crossoverProbability->Value = 80;
		this->comboBox_mutationMethod->SelectedItem = "none";
		this->numericUpDown_mutationProbability->Value = 0;
	}

	private: System::Void button_cancel_Click(System::Object^  sender, System::EventArgs^  e) {
		ConfigurationForm::Close();
	}

	// ----------------------------------------------------------------------------------------------------------


	// CONFIGURATION CHECK EVENTS -------------------------------------------------------------------------------

	// changes in following controls require configuration check which prevents from creating impossible configuration

	private: bool previousAFactorWasPositive01; // true when previous aFactor was equal to 0.1
	private: bool previousAFactorWasNegative01; // true when previous aFactor was equal to -0.1
	private: System::Void numericUpDown_aFactor_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		// avoding aFactor from being equal to 0
		if (previousAFactorWasPositive01 == true) {
			if (this->numericUpDown_aFactor->Value == 0) {
				this->numericUpDown_aFactor->Value = Convert::ToDecimal(-0.1);
			}
			this->previousAFactorWasPositive01 = false;
		}
		if (this->previousAFactorWasNegative01 == true) {
			if (this->numericUpDown_aFactor->Value == 0) {
				this->numericUpDown_aFactor->Value = Convert::ToDecimal(0.1);
			}
			this->previousAFactorWasNegative01 = false;
		}
		if (this->numericUpDown_aFactor->Value == Convert::ToDecimal(0.1)) {
			this->previousAFactorWasPositive01 = true;
		}
		else if (this->numericUpDown_aFactor->Value == Convert::ToDecimal(-0.1)) {
			this->previousAFactorWasNegative01 = true;
		}
	}

	private: System::Void comboBox_codingMethod_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

		// cannot apply 'gene negation' mutation when coding method 'integers' is chosen
		System::String^ chosenCodingMethod = gcnew System::String(comboBox_codingMethod->Text);
		System::String^ chosenMutationMethod = gcnew System::String(comboBox_mutationMethod->Text);
		if (!chosenCodingMethod->Equals("integers")) {
			this->comboBox_mutationMethod->Items->Clear();
			this->comboBox_mutationMethod->Items->AddRange(gcnew cli::array< System::Object^>(4) { L"none", L"gene negation", L"gene swap", L"permutation" });
			if (chosenMutationMethod->Equals("none")) this->comboBox_mutationMethod->SelectedItem = "none";
			else if (chosenMutationMethod->Equals("gene negation")) this->comboBox_mutationMethod->SelectedItem = "gene negation";
			else if (chosenMutationMethod->Equals("gene swap")) this->comboBox_mutationMethod->SelectedItem = "gene swap";
			else if (chosenMutationMethod->Equals("permutation")) this->comboBox_mutationMethod->SelectedItem = "permutation";
			else if (chosenMutationMethod->Equals("")) {} // needed on first SetUp when 'Coding method' is set before 'Mutation method' is set
			else throw gcnew System::ArgumentException("Invalid mutation method (CofigurationForm.h|configurationCheck)");
		}
		else { // (chosenCodingMethod->Equals("integers"))
			this->comboBox_mutationMethod->Items->Clear();
			this->comboBox_mutationMethod->Items->AddRange(gcnew cli::array< System::Object^>(3) { L"none", L"gene swap", L"permutation" });
			if (chosenMutationMethod->Equals("none")) this->comboBox_mutationMethod->SelectedItem = "none";
			else if (chosenMutationMethod->Equals("gene negation")) this->comboBox_mutationMethod->SelectedItem = "none";
			else if (chosenMutationMethod->Equals("gene swap")) this->comboBox_mutationMethod->SelectedItem = "gene swap";
			else if (chosenMutationMethod->Equals("permutation")) this->comboBox_mutationMethod->SelectedItem = "permutation";
			else if (chosenMutationMethod->Equals("")) {} // needed on first SetUp when 'Coding method' is set before 'Mutation method' is set
			else throw gcnew System::ArgumentException("Invalid mutation method (CofigurationForm.h|configurationCheck)");
		}

		// cannot apply 'averaging' crossover when coding method 'binary8' or 'binary10' is chosen
		System::String^ chosenCrossoverMethod = gcnew System::String(comboBox_crossoverMethod->Text);
		if (chosenCodingMethod->Equals("binary8") || chosenCodingMethod->Equals("binary10")) {
			this->comboBox_crossoverMethod->Items->Clear();
			this->comboBox_crossoverMethod->Items->AddRange(gcnew cli::array< System::Object^>(3) { L"one point crossover", L"two point crossover", L"uniform crossover" });
			if (chosenCrossoverMethod->Equals("one point crossover")) this->comboBox_crossoverMethod->SelectedItem = "one point crossover";
			else if (chosenCrossoverMethod->Equals("two point crossover")) this->comboBox_crossoverMethod->SelectedItem = "two point crossover";
			else if (chosenCrossoverMethod->Equals("uniform crossover")) this->comboBox_crossoverMethod->SelectedItem = "uniform crossover";
			else if (chosenCrossoverMethod->Equals("averaging")) this->comboBox_crossoverMethod->SelectedItem = "one point crossover";
			else if (chosenCrossoverMethod->Equals("")) {} // needed on first SetUp when 'Coding method' is set before 'Crossover method' is set
			else throw gcnew System::ArgumentException("Invalid crossover method (CofigurationForm.h|configurationCheck)");
		}
		else { // !(chosenCodingMethod->Equals("binary8") || chosenCodingMethod->Equals("binary10"))
			this->comboBox_crossoverMethod->Items->Clear();
			this->comboBox_crossoverMethod->Items->AddRange(gcnew cli::array< System::Object^>(4) { L"one point crossover", L"two point crossover", L"uniform crossover", L"averaging" });
			if (chosenCrossoverMethod->Equals("one point crossover")) this->comboBox_crossoverMethod->SelectedItem = "one point crossover";
			else if (chosenCrossoverMethod->Equals("two point crossover")) this->comboBox_crossoverMethod->SelectedItem = "two point crossover";
			else if (chosenCrossoverMethod->Equals("uniform crossover")) this->comboBox_crossoverMethod->SelectedItem = "uniform crossover";
			else if (chosenCrossoverMethod->Equals("averaging")) this->comboBox_crossoverMethod->SelectedItem = "averaging";
			else if (chosenCrossoverMethod->Equals("")) {} // needed on first SetUp when 'Coding method' is set before 'Crossover method' is set
			else throw gcnew System::ArgumentException("Invalid crossover mutation method (CofigurationForm.h|configurationCheck)");
		}

	}

	private: System::Void comboBox_mutationMethod_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

		// for 'none' mutation method 'mutation probability' numericalUpDown should be switched off
		if (this->comboBox_mutationMethod->Text->Equals("none")) {
			this->numericUpDown_mutationProbability->Value = 0;
			this->numericUpDown_mutationProbability->Enabled = false;
		}
		else this->numericUpDown_mutationProbability->Enabled = true;

	}

	// ----------------------------------------------------------------------------------------------------------


	};
}