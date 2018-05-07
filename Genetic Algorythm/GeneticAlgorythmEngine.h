#pragma once

#ifndef GeneticAlgorythmEngine_h
#define GeneticAlgorythmEngine_h


// MODES --------------------------------------------------------------------------------------------

enum class codingMethod { binary8, binary10, integers };

enum class target { maximum, minimum, ekstremum };
enum class fitnessFunctionType { linear, exponential };
enum class selectionMethod { roulette, ranking, tournament };
enum class selectionModification { none, eliteSelection, partialExchange };
enum class crossoverMethod { onePointCrossover, twoPointCrossover, uniformCrossover, averaging };
enum class mutationMethod { none, geneNegation, geneSwap, permutation };

// --------------------------------------------------------------------------------------------------


// CLASS PARAMETERS ---------------------------------------------------------------------------------

public ref class Parameters {

	// contructor, copy contructor, destructor, assignment operator
public:
	Parameters(); // sets default parameters
	Parameters(Parameters^ other);
	~Parameters();
	Parameters^ operator=(Parameters^ other);

	// fields
private:
	// population parameters
	int populationSize;
	codingMethod flag_codingMethod;
private:
	// genetic algorythm parameters
	target flag_target;
	fitnessFunctionType flag_fitnessFunctionType;
	selectionMethod flag_selectionMethod;
	selectionModification flag_selectionModification;
	crossoverMethod flag_crossoverMethod;
	mutationMethod flag_mutationMethod;
	int crossoverProbability;
	int mutationProbability;
private:
	// chart parameters
	double aFactor;
	double bFactor;
	double cFactor;

	// properties
public:
	// population parameters
	property int PopulationSize {
		void set(int size) {
			this->populationSize = size;
		}
		int get() {
			return this->populationSize;
		}
	}
	property codingMethod Flag_codingMethod {
		void set(codingMethod flag) {
			this->flag_codingMethod = flag;
		}
		codingMethod get() {
			return this->flag_codingMethod;
		}
	}
public:
	// genetic algorythm parameters
	property target Flag_target {
		void set(target flag) {
			this->flag_target = flag;
		}
		target get() {
			return this->flag_target;
		}
	}
	property fitnessFunctionType Flag_fitnessFunctionType {
		void set(fitnessFunctionType flag) {
			this->flag_fitnessFunctionType = flag;
		}
		fitnessFunctionType get() {
			return this->flag_fitnessFunctionType;
		}
	}
	property selectionMethod Flag_selectionMethod {
		void set(selectionMethod flag) {
			this->flag_selectionMethod = flag;
		}
		selectionMethod get() {
			return this->flag_selectionMethod;
		}
	}
	property selectionModification Flag_selectionModification {
		void set(selectionModification flag) {
			this->flag_selectionModification = flag;
		}
		selectionModification get() {
			return this->flag_selectionModification;
		}
	}
	property crossoverMethod Flag_crossoverMethod {
		void set(crossoverMethod flag) {
			this->flag_crossoverMethod = flag;
		}
		crossoverMethod get() {
			return this->flag_crossoverMethod;
		}
	}
	property mutationMethod Flag_mutationMethod {
		void set(mutationMethod flag) {
			this->flag_mutationMethod = flag;
		}
		mutationMethod get() {
			return this->flag_mutationMethod;
		}
	}
	property int CrossoverProbability {
		void set(int probability) {
			this->crossoverProbability = probability;
		}
		int get() {
			return this->crossoverProbability;
		}
	}
	property int MutationProbability {
		void set(int probability) {
			this->mutationProbability = probability;
		}
		int get() {
			return this->mutationProbability;
		}
	}
public:
	// chart parameters
	property double AFactor {
		void set(double factor) {
			this->aFactor = factor;
		}
		double get() {
			return this->aFactor;
		}
	}
	property double BFactor {
		void set(double factor) {
			this->bFactor = factor;
		}
		double get() {
			return this->bFactor;
		}
	}
	property double CFactor {
		void set(double factor) {
			this->cFactor = factor;
		}
		double get() {
			return this->cFactor;
		}
	}
};

// --------------------------------------------------------------------------------------------------


// CLASS INDIVIDUAL ---------------------------------------------------------------------------------

public ref class Individual {
public:
	Individual(codingMethod codMet, int seed);
	Individual(Individual^ other);
	~Individual();
public: // methods
	int getEncodedValue();
private: // fields
	codingMethod flag_codingMethod;
	array<char> ^genome;
	double fitnessFunctionValue;
public: // properties
	property codingMethod Flag_codingMethod {
		void set(codingMethod flag) {
			this->flag_codingMethod = flag;
		}
		codingMethod get() {
			return this->flag_codingMethod;
		}
	}
	property array<char> ^Genome {
		void set(array<char> ^otherGenome) {
			this->genome = otherGenome;
		}
		array<char>^ get() {
			return this->genome;
		}
	}
	property double FitnessFunctionValue {
		void set(double value) {
			this->fitnessFunctionValue = value;
		}
		double get() {
			return this->fitnessFunctionValue;
		}
	}
};

// --------------------------------------------------------------------------------------------------


// CLASS POPULATION ---------------------------------------------------------------------------------

public ref class Population {

public: // contructors, copy constructor, assignment operator, destructor
	Population(Parameters^ config);	// initializes population
	Population(Population^ other);
	Population^ operator= (Population^ other);
	~Population();

private: // internal methods
	void initialize();

private: // fields
	Parameters^ internalConfig;
	array<Individual^> ^populationMembers;

public: // properties
	property Parameters^ InternalConfig {
		void set(Parameters^ config) {
			this->internalConfig = config;
		}
		Parameters^ get() {
			return this->internalConfig;
		}
	}
	property array<Individual^> ^PopulationMembers {
		void set(array<Individual^> ^other) {
			this->populationMembers = other;
		}
		array<Individual^>^ get() {
			return this->populationMembers;
		}
	}
};

// --------------------------------------------------------------------------------------------------



// CLASS CHART & CLASS COORDINATES ------------------------------------------------------------------

public ref class Coordinates {
public:
	Coordinates(double arg, double val);
	~Coordinates();
private: // fields
	double x;
	double y;
public: // properties
	property double X {
		void set(double value) {
			this->x = value;
		}
		double get() {
			return this->x;
		}
	}
	property double Y {
		void set(double value) {
			this->y = value;
		}
		double get() {
			return this->y;
		}
	}
};


public ref class Chart {

public:
	Chart(Parameters^ config, Population^ individuals);
	~Chart();

private: // internal methods
	void basicChartPropertiesSetup();
	void drawParabola();
	void drawPoints();
	double computeAveragePointsValue();
	double findBestIndividual();
	double computeRealization();
	double computeParabolaValue(double argument);

private: // fields
	Parameters^ internalConfig;
	Population^ internalPopulation;
	array<Coordinates^> ^parabola;
	array<Coordinates^> ^points;
	int rangeStartArgument;
	double parabolaPeakArgument;
	int rangeEndArgument;
	double targetArgument;
	double highestChartValue;
	double lowestChartValue;
	double targetValue;
	double averagePointsValue;
	double bestIndividual;
	double realizationPercentage;

public: // properties
	property Parameters^ InternalConfig {
		void set(Parameters^ config) {
			this->internalConfig = config;
		}
		Parameters^ get() {
			return this->internalConfig;
		}
	}
	property Population^ InternalPopulation {
		void set(Population^ population) {
			this->internalPopulation = population;
		}
		Population^ get() {
			return this->internalPopulation;
		}
	}
	property array<Coordinates^> ^Parabola {
		void set(array<Coordinates^> ^otherParabola) {
			this->parabola = otherParabola;
		}
		array<Coordinates^>^ get() {
			return this->parabola;
		}
	}
	property array<Coordinates^> ^Points {
		void set(array<Coordinates^> ^otherPoints) {
			this->points = otherPoints;
		}
		array<Coordinates^>^ get() {
			return this->points;
		}
	}
	property int RangeStartArgument {
		void set(int argument) {
			this->rangeStartArgument = argument;
		}
		int get() {
			return this->rangeStartArgument;
		}
	}
	property double ParabolaPeakArgument {
		void set(double argument) {
			this->parabolaPeakArgument = argument;
		}
		double get() {
			return this->parabolaPeakArgument;
		}
	}
	property int RangeEndArgument {
		void set(int argument) {
			this->rangeEndArgument = argument;
		}
		int get() {
			return this->rangeEndArgument;
		}
	}
	property double TargetArgument {
		void set(double argument) {
			this->targetArgument = argument;
		}
		double get() {
			return this->targetArgument;
		}
	}
	property double HighestChartValue {
		void set(double value) {
			this->highestChartValue = value;
		}
		double get() {
			return this->highestChartValue;
		}
	}
	property double LowestChartValue {
		void set(double value) {
			this->lowestChartValue = value;
		}
		double get() {
			return this->lowestChartValue;
		}
	}
	property double TargetValue {
		void set(double value) {
			this->targetValue = value;
		}
		double get() {
			return this->targetValue;
		}
	}
	property double AveragePointsValue {
		void set(double value) {
			this->averagePointsValue = value;
		}
		double get() {
			return this->averagePointsValue;
		}
	}
	property double BestIndividual {
		void set(double individual) {
			this->bestIndividual = individual;
		}
		double get() {
			return this->bestIndividual;
		}
	}
	property double RealizationPercentage {
		void set(double percentage) {
			this->realizationPercentage = percentage;
		}
		double get() {
			return this->realizationPercentage;
		}
	}
};

// --------------------------------------------------------------------------------------------------



// GENETICALGORYTHMTOOLBOX CHART --------------------------------------------------------------------

public ref class GeneticAlgorythmToolbox {

public: // contructor, destructor
	GeneticAlgorythmToolbox(Parameters^ config);
	~GeneticAlgorythmToolbox();

public: // methods
	void evolve(Population^ individuals);

private: // internal methods
	void assignFitnessFunctionValues(Population^ individuals);
	void selectParents(Population^ individuals);
	void crossover(Population^ parents);
	void mutate(Population^ individuals);
	void applySelectionModification(Population^ individuals);
private: // auxiliary internal methods
	double computeParabolaValue(double argument);
	void permutate(char* genes, int quantity);
private: // auxiliary internal fields
	array<Individual^> ^sorted;
	System::Random ^rand;

private: // fields
	Parameters^ internalConfig;

public: // properties
	Parameters^ InternalConfig;
};

// --------------------------------------------------------------------------------------------------


#endif