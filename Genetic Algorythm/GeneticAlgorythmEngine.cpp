
#include "stdafx.h"

#include "GeneticAlgorythmEngine.h"


// CLASS OF FLAGS AND PARAMETERS --------------------------------------------------------------------

Parameters::Parameters()
{
	// setting default configuration
	this->populationSize = 10;
	this->flag_codingMethod = codingMethod::binary8;

	this->flag_target = target::maximum;
	this->flag_fitnessFunctionType = fitnessFunctionType::linear;
	this->flag_selectionMethod = selectionMethod::roulette;
	this->flag_selectionModification = selectionModification::none;
	this->flag_crossoverMethod = crossoverMethod::onePointCrossover;
	this->flag_mutationMethod = mutationMethod::none;
	this->crossoverProbability = 80;
	this->mutationProbability = 0;

	this->aFactor = -0.1;
	this->bFactor = 1;
	this->cFactor = 10;
}

Parameters::Parameters(Parameters^ other)
{
	this->populationSize = other->PopulationSize;
	this->flag_codingMethod = other->Flag_codingMethod;

	this->flag_target = other->Flag_target;
	this->flag_fitnessFunctionType = other->Flag_fitnessFunctionType;
	this->flag_selectionMethod = other->Flag_selectionMethod;
	this->flag_selectionModification = other->Flag_selectionModification;
	this->flag_crossoverMethod = other->Flag_crossoverMethod;
	this->flag_mutationMethod = other->Flag_mutationMethod;
	this->crossoverProbability = other->CrossoverProbability;
	this->mutationProbability = other->MutationProbability;

	this->aFactor = other->AFactor;
	this->bFactor = other->BFactor;
	this->cFactor = other->CFactor;
}

Parameters::~Parameters()
{}

Parameters ^ Parameters::operator=(Parameters ^ other)
{
	this->populationSize = other->PopulationSize;
	this->flag_codingMethod = other->Flag_codingMethod;

	this->flag_target = other->Flag_target;
	this->flag_fitnessFunctionType = other->Flag_fitnessFunctionType;
	this->flag_selectionMethod = other->Flag_selectionMethod;
	this->flag_selectionModification = other->Flag_selectionModification;
	this->flag_crossoverMethod = other->Flag_crossoverMethod;
	this->flag_mutationMethod = other->Flag_mutationMethod;
	this->crossoverProbability = other->CrossoverProbability;
	this->mutationProbability = other->MutationProbability;

	this->aFactor = other->AFactor;
	this->bFactor = other->BFactor;
	this->cFactor = other->CFactor;

	return this;
}

// --------------------------------------------------------------------------------------------------



// CLASS INDIVIDUAL ---------------------------------------------------------------------------------

Individual::Individual(codingMethod codMet, int seed)
	: flag_codingMethod(codMet)
{
	// setting instance of rand
	System::Random ^rand = gcnew System::Random(seed);
	// creating genomes randomly
	switch (flag_codingMethod) {
	case codingMethod::binary8:
		genome = gcnew array<char>(8);
		for (int i = 0; i < 8; i++) { genome[i] = static_cast<char>(rand->Next(0,2)); } // 0-1
		FitnessFunctionValue = 0; // sets fitness function value for 0
		break;
	case codingMethod::binary10:
		genome = gcnew array<char>(10);
		for (int i = 0; i < 10; i++) { genome[i] = static_cast<char>(rand->Next(0,2)); } // 0-1
		FitnessFunctionValue = 0; // sets fitness function value for 0
		break;
	case codingMethod::integers:
		genome = gcnew array<char>(4);
		for (int i = 0; i < 4; i++) { genome[i] = static_cast<char>(rand->Next(0,10)); } // 0-9
		FitnessFunctionValue = 0; // sets fitness function value for 0
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|Individual|default constructor)");
		break;
	}
}

Individual::Individual(Individual^ other)
{
	// prescribing coding method
	flag_codingMethod = other->Flag_codingMethod;
	// prescribing genome
	switch (flag_codingMethod)
	{
	case codingMethod::binary8:
		genome = gcnew array<char>(8);
		for (int i = 0; i < 8; i++) {
			genome[i] = other->Genome[i];
		}
		break;
	case codingMethod::binary10:
		genome = gcnew array<char>(10);
		for (int i = 0; i < 10; i++) {
			genome[i] = other->Genome[i];
		}
		break;
	case codingMethod::integers:
		genome = gcnew array<char>(4);
		for (int i = 0; i < 4; i++) {
			genome[i] = other->Genome[i];
		}
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|Individual|copy constructor)");
		break;
	}
	// prescribing fitness function value
	fitnessFunctionValue = other->FitnessFunctionValue;
}

Individual::~Individual()
{}

int Individual::getEncodedValue()
{
	int encodedValue = 0;

	switch (flag_codingMethod) {
	case codingMethod::binary8:
		for (int i = 0; i < 8; i++)
		{
			encodedValue += static_cast<int>(static_cast<int>(genome[7 - i]) * System::Math::Pow(2, i));
		}
		return encodedValue;
		break;
	case codingMethod::binary10:
		for (int i = 0; i < 10; i++)
		{
			encodedValue += static_cast<int>(static_cast<int>(genome[9 - i]) * System::Math::Pow(2, i));
		}
		return encodedValue;
		break;
	case codingMethod::integers:
		for (int i = 0; i < 4; i++)
		{
			encodedValue += static_cast<int>(static_cast<int>(genome[3 - i]) * System::Math::Pow(10, i));
		}
		return encodedValue;
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|Individual|getEncodedValue)");
		break;
	}
}

// --------------------------------------------------------------------------------------------------



// CLASS POPULATION ---------------------------------------------------------------------------------

Population::Population(Parameters^ config)
{
	this->internalConfig = config;
	// population initialization
	initialize();
}

Population::Population(Population^ other)
{
	this->internalConfig = gcnew Parameters(other->InternalConfig);
	this->populationMembers = gcnew array<Individual^>(internalConfig->PopulationSize);
	for (int i = 0; i < internalConfig->PopulationSize; i++) {
		populationMembers[i] = gcnew Individual(other->PopulationMembers[i]);
	}
}

Population^ Population::operator= (Population^ other)
{
	this->internalConfig = gcnew Parameters(other->InternalConfig);
	this->populationMembers = gcnew array<Individual^>(internalConfig->PopulationSize);
	for (int i = 0; i < internalConfig->PopulationSize; i++) {
		populationMembers[i] = gcnew Individual(other->PopulationMembers[i]);
	}

	return this;
}

Population::~Population()
{}

void Population::initialize()
{
	// size check
	if (internalConfig->PopulationSize < 1)
	{
		throw gcnew System::ArgumentException("Invalid population size (GeneticAlgorythmEngine.cpp|Population|Initialize)");
	}


	// creating random seed to pass to Individual default constructor
	System::Random ^rand = gcnew System::Random();

	// creating population members
	populationMembers = gcnew array<Individual^>(internalConfig->PopulationSize);
	for (int i = 0; i < internalConfig->PopulationSize; i++)
	{
		populationMembers[i] = gcnew Individual(internalConfig->Flag_codingMethod, rand->Next(0,1000000));
	}
}

// --------------------------------------------------------------------------------------------------



// CLASS CHART & CLASS COORDINATES ------------------------------------------------------------------

Coordinates::Coordinates(double arg, double val)
	: x(arg)
	, y(val)
{}

Coordinates::~Coordinates()
{}


Chart::Chart(Parameters^ config, Population^ individuals)
	: internalConfig(config)
	, internalPopulation(individuals)
{
	// setting basic chart properties
	basicChartPropertiesSetup();

	// setting up containers for parabola and points coordinates
	parabola = gcnew array<Coordinates^>(1280); // 64 / 0.05 = 1280 (0.05 is an interval between parabola points)
	points = gcnew array<Coordinates^>(internalPopulation->InternalConfig->PopulationSize);

	// drawing parabola and population points
	drawParabola();
	drawPoints();

	// computing average points value
	averagePointsValue = computeAveragePointsValue();

	// finding best individual
	bestIndividual = findBestIndividual();

	// computing progress percentage
	realizationPercentage = computeRealization();
}

Chart::~Chart()
{}

void Chart::basicChartPropertiesSetup()
{
	// setting parabola chart parameters
	parabolaPeakArgument = -(internalConfig->BFactor) / (2 * internalConfig->AFactor); // -b/2a
	double parabolaPeakValue = computeParabolaValue(parabolaPeakArgument);
	// value for parabola peak argument is highest or lowest on the chart depending on aFactor sign
	if (parabolaPeakArgument - 32 >= 0) {
		rangeStartArgument = static_cast<int>(parabolaPeakArgument - 32); // first integer on the left from parabolaPeak - 32
	}
	else { // (parabolaPeakArgument - 32 < 0)
		rangeStartArgument = static_cast<int>(parabolaPeakArgument - 32) - 1; // first integer on the left from parabolaPeak - 32
	}
	rangeEndArgument = rangeStartArgument + 64;
	double rangeStartValue = computeParabolaValue(rangeStartArgument);
	// value for range start argument is highest or lowest on the chart depending on aFactor sign

	// setting highest/lowest value & target argument/value
	if (internalConfig->AFactor > 0) {
		highestChartValue = rangeStartValue;
		lowestChartValue = parabolaPeakValue;
		switch (internalConfig->Flag_target) {
		case target::maximum:
			targetArgument = rangeStartArgument;
			targetValue = highestChartValue;
			break;
		case target::minimum:
			targetArgument = parabolaPeakArgument;
			targetValue = lowestChartValue;
			break;
		case target::ekstremum:
			targetArgument = parabolaPeakArgument;
			targetValue = lowestChartValue;
			break;
		default:
			throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
			break;
		}
	}
	else if (internalConfig->AFactor < 0) {
		highestChartValue = parabolaPeakValue;
		lowestChartValue = rangeStartValue;
		switch (internalConfig->Flag_target) {
		case target::maximum:
			targetArgument = parabolaPeakArgument;
			targetValue = highestChartValue;
			break;
		case target::minimum:
			targetArgument = rangeStartArgument;
			targetValue = lowestChartValue;
			break;
		case target::ekstremum:
			targetArgument = parabolaPeakArgument;
			targetValue = highestChartValue;
			break;
		default:
			throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
			break;
		}
	}
	else { // (internalConfig->AFactor == 0)
		if (internalConfig->BFactor > 0) {
			highestChartValue = computeParabolaValue(rangeEndArgument);
			lowestChartValue = rangeStartValue;
			switch (internalConfig->Flag_target) {
			case target::maximum:
				targetArgument = rangeEndArgument;
				targetValue = highestChartValue;
				break;
			case target::minimum:
				targetArgument = rangeStartArgument;
				targetValue = lowestChartValue;
				break;
			case target::ekstremum: throw gcnew System::ArgumentException("No extremum target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
				break;
			default:
				throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
				break;
			}
		}
		else if (internalConfig->BFactor < 0) {
			highestChartValue = rangeStartValue;
			lowestChartValue = computeParabolaValue(rangeEndArgument);
			switch (internalConfig->Flag_target) {
			case target::maximum:
				targetArgument = rangeStartArgument;
				targetValue = highestChartValue;
				break;
			case target::minimum:
				targetArgument = rangeEndArgument;
				targetValue = lowestChartValue;
				break;
			case target::ekstremum: throw gcnew System::ArgumentException("No extremum target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
				break;
			default:
				throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
				break;
			}
		}
		else { // (internalConfig->BFactor == 0)
			throw gcnew System::ArgumentException("No target (GeneticAlgorythmEngine.cpp|Chart|basicChartPropertiesSetup)");
		}
	}
}

void Chart::drawParabola()
{
	// filling array of parabola coordinates
	double x = rangeStartArgument, y = 0;
	for (int i = 0; i < 1280; i++) // 1280 = 64 / 0.05 (0.05 is an interval between parabola points)
	{
		y = computeParabolaValue(x);
		parabola[i] = gcnew Coordinates(x, y);
		x += 0.05;
	}
}

void Chart::drawPoints()
{
	// mapping individuals on chart
	double elementaryInterval = 0; // smallest interval between two arguments represented by genome of individual
	int encodedNumber = 0; // number encoded in individual's genome
	double x = 0; // argument represented by genome of individual
	double y = 0; // value of function computed for given argument

				  // setting elementary interval
	switch (internalPopulation->InternalConfig->Flag_codingMethod)
	{
	case codingMethod::binary8:
		elementaryInterval = 0.25; // 64 / 256
		break;
	case codingMethod::binary10:
		elementaryInterval = 0.0625; // 64 / 1024
		break;
	case codingMethod::integers:
		elementaryInterval = 0.0064; // 64 / 10000
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|Chart|drawPoints)");
		break;
	}

	// filling array of point coordinates
	for (int i = 0; i < internalPopulation->InternalConfig->PopulationSize; i++)
	{
		encodedNumber = internalPopulation->PopulationMembers[i]->getEncodedValue();
		x = rangeStartArgument + encodedNumber * elementaryInterval;
		y = computeParabolaValue(x);
		points[i] = gcnew Coordinates(x, y);
	}
}

double Chart::computeAveragePointsValue()
{
	// summing up all values of points (data from internal array of points)
	double sum = 0;
	for (int i = 0; i < internalPopulation->InternalConfig->PopulationSize; i++) {
		sum += points[i]->Y;
	}
	return sum / (internalPopulation->InternalConfig->PopulationSize);
}

double Chart::findBestIndividual()
{
	// function looks for individual closest to target argument (data from internal array of points)
	double closestIndividual = points[0]->X;
	double minimumDeviation = System::Math::Abs(targetArgument - closestIndividual);
	for (int i = 1; i < internalPopulation->InternalConfig->PopulationSize; i++) {
		if (System::Math::Abs(targetArgument - points[i]->X) < minimumDeviation) {
			closestIndividual = points[i]->X;
			minimumDeviation = System::Math::Abs(targetArgument - closestIndividual);
		}
	}
	return closestIndividual;
}

double Chart::computeRealization()
{
	double elementaryInterval = 0; // smallest interval between two arguments represented by genome of individual
	double maximumDeviation = 0; // maximum integer number of elementary intervals counted from target point
	double deviation = 0; // actual integer number of elementary intervals counted from target point

	switch (internalPopulation->InternalConfig->Flag_codingMethod)
	{
	case codingMethod::binary8:
		elementaryInterval = 0.25; // 64 / 256
		break;
	case codingMethod::binary10:
		elementaryInterval = 0.0625; // 64 / 1024
		break;
	case codingMethod::integers:
		elementaryInterval = 0.0064; // 64 / 10000
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|Chart|computeRealization)");
		break;
	}

	// determining maximumDeviation and deviation of the best individual in population
	if (targetArgument == parabolaPeakArgument) {
		maximumDeviation = System::Math::Floor((parabolaPeakArgument - rangeStartArgument) / elementaryInterval);
	}
	else { // (targetArgument == rangeStartArgument || targetArgument == rangeEndArgument)
		maximumDeviation = System::Math::Floor((rangeEndArgument - rangeStartArgument) / elementaryInterval);
	}
	deviation = System::Math::Floor(System::Math::Abs(targetArgument - bestIndividual) / elementaryInterval);

	return ((maximumDeviation - deviation) / maximumDeviation) * 100;
}

double Chart::computeParabolaValue(double argument)
{
	// function computes value for given argument
	return internalConfig->AFactor * System::Math::Pow(argument, 2) + internalConfig->BFactor * argument + internalConfig->CFactor;
}

// --------------------------------------------------------------------------------------------------



// GENETICALGORYTHMTOOLBOX --------------------------------------------------------------------------

GeneticAlgorythmToolbox::GeneticAlgorythmToolbox(Parameters^ config)
	: internalConfig(config)
{
	rand = gcnew System::Random();
}

GeneticAlgorythmToolbox::~GeneticAlgorythmToolbox()
{}

void GeneticAlgorythmToolbox::evolve(Population^ individuals)
{
	assignFitnessFunctionValues(individuals);

	selectParents(individuals);

	crossover(individuals);

	if (internalConfig->Flag_mutationMethod != mutationMethod::none) { mutate(individuals); }

	if (internalConfig->Flag_selectionModification != selectionModification::none) { applySelectionModification(individuals); }
}

void GeneticAlgorythmToolbox::assignFitnessFunctionValues(Population^ individuals)
{
	// setting parabola chart parameters
	double parabolaPeakArgument = -(internalConfig->BFactor) / (2 * internalConfig->AFactor); // -b/2a
	double parabolaPeakValue = computeParabolaValue(parabolaPeakArgument);
	// value for parabola peak argument is highest or lowest on the chart depending on aFactor sign
	int rangeStartArgument = 0; // first integer on the left from parabolaPeak - 32
	if (parabolaPeakArgument - 32 >= 0) {
		rangeStartArgument = static_cast<int>(parabolaPeakArgument - 32);
	}
	else { // (parabolaPeakArgument - 32 < 0)
		rangeStartArgument = static_cast<int>(parabolaPeakArgument - 32) - 1;
	}
	int rangeEndArgument = rangeStartArgument + 64;
	double rangeStartValue = computeParabolaValue(rangeStartArgument);
	// value for range start argument is highest or lowest on the chart depending on aFactor sign

	double highestChartValue = 0;
	double lowestChartValue = 0;
	if (internalConfig->AFactor > 0) {
		highestChartValue = rangeStartValue;
		lowestChartValue = parabolaPeakValue;
	}
	else if (internalConfig->AFactor < 0) {
		highestChartValue = parabolaPeakValue;
		lowestChartValue = rangeStartValue;
	}
	else { // (internalConfig->AFactor == 0)
		if (internalConfig->BFactor >= 0) {
			highestChartValue = computeParabolaValue(rangeEndArgument);
			lowestChartValue = rangeStartValue;
		}
		else { // (internalConfig->BFactor < 0)
			highestChartValue = rangeStartValue;
			lowestChartValue = computeParabolaValue(rangeEndArgument);
		}
	}

	// mapping individuals on chart
	double elementaryInterval = 0; // smallest interval between two arguments represented by genome of individual
	int encodedNumber = 0; // number encoded in individual's genome
	double x = 0; // argument represented by genome of individual
	double y = 0; // value of function computed for given argument

	switch (individuals->InternalConfig->Flag_codingMethod)
	{
	case codingMethod::binary8:
		elementaryInterval = 0.25; // 64 / 256
		break;
	case codingMethod::binary10:
		elementaryInterval = 0.0625; // 64 / 1024
		break;
	case codingMethod::integers:
		elementaryInterval = 0.0064; // 64 / 10000
		break;
	default:
		throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
		break;
	}

	// setting fitness function value
	double value = 0;

	for (int i = 0; i < internalConfig->PopulationSize; i++)
	{
		encodedNumber = individuals->PopulationMembers[i]->getEncodedValue();
		x = rangeStartArgument + encodedNumber * elementaryInterval;
		y = computeParabolaValue(x);

		if (internalConfig->Flag_fitnessFunctionType == fitnessFunctionType::linear) {

			switch (internalConfig->Flag_target)
			{
			case target::maximum:

				value = y - lowestChartValue;
				// value will be >= 0
				// ^ formula works for lowestChartValue positive, negative and equal 0
				break;

			case target::minimum:

				value = y - lowestChartValue; // value will be >= 0
				value = (highestChartValue - lowestChartValue) - y; // value inversion (value still >= 0)
																	// ^ formula works for lowestChartValue positive, negative and equal 0
				break;

			case target::ekstremum:

				if (internalConfig->AFactor > 0) { // looking for minimum

					value = y - lowestChartValue; // value will be >= 0
					value = (highestChartValue - lowestChartValue) - y; // value inversion (value still >= 0)
																		// ^ formula works for lowestChartValue positive, negative and equal 0

				}
				else if (internalConfig->AFactor < 0) { // looking for maximum

					value = y - lowestChartValue;
					// value will be >= 0
					// ^ formula works for lowestChartValue positive, negative and equal 0

				}
				else { // (internalConfig->AFactor == 0
					throw gcnew System::InvalidOperationException("Cannot look for extremum of linear funciton (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
				}
				break;

			default:
				throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
				break;
			}

		}
		else if (internalConfig->Flag_fitnessFunctionType == fitnessFunctionType::exponential) {

			switch (internalConfig->Flag_target)
			{
			case target::maximum:

				value = System::Math::Pow(2, y / 20);
				// exponent function is always positive (dividing y value by 20 : don't want it to be too high)
				break;

			case target::minimum:

				value = System::Math::Pow(2, -y / 20); // value inversion
													   // exponent function is always positive (dividing y value by 20 : don't want it to be too high)
				break;

			case target::ekstremum:

				if (internalConfig->AFactor > 0) { // looking for minimum

					value = System::Math::Pow(2, -y / 20); // value inversion
														   // exponent function is always positive (dividing y value by 20 : don't want it to be too high)

				}
				else if (internalConfig->AFactor < 0) { // looking for maximum

					value = System::Math::Pow(2, y / 20);
					// exponent function is always positive (dividing y value by 20 : don't want it to be too high)

				}
				else { // (internalConfig->AFactor == 0
					throw gcnew System::InvalidOperationException("Cannot look for extremum of linear funciton (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
				}
				break;

			default:
				throw gcnew System::ArgumentException("Invalid target (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
				break;
			}

		}
		else {
			throw gcnew System::ArgumentException("Invalid fitness function type (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|assignFitnessFunctionValues)");
		}

		// assigning  fitness function value to individual
		individuals->PopulationMembers[i]->FitnessFunctionValue = value;

	}

}


void GeneticAlgorythmToolbox::selectParents(Population^ individuals)
{
	// selection modifications preparation
	int populationSize = individuals->InternalConfig->PopulationSize;
	sorted = gcnew array<Individual^>(populationSize); // from best to worst
													   // prescribing individual handles to sorted array
	for (int i = 0; i < populationSize; i++) {
		sorted[i] = individuals->PopulationMembers[i];
	}
	// bubble sort
	int numbersOfShifts = -1;
	while (numbersOfShifts != 0)
	{
		numbersOfShifts = 0;
		for (int i = 0; i < populationSize - 1; i++) {
			if (sorted[i]->FitnessFunctionValue < sorted[i + 1]->FitnessFunctionValue)
			{
				Individual^ temporary = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = temporary;
				numbersOfShifts++;
			}
		}
	} // end of preparation (sorted array is also used in ranking method of selection)


	switch (internalConfig->Flag_selectionMethod) {

	case selectionMethod::roulette: {

		double totalValue = 0; // all fitness function values summed up
		for (int i = 0; i < populationSize; i++) {
			totalValue += individuals->PopulationMembers[i]->FitnessFunctionValue;
		}
		// computing percentages attributable to each individual
		array<double> ^percentages = gcnew array<double>(populationSize);
		for (int i = 0; i < populationSize; i++) {
			percentages[i] = (individuals->PopulationMembers[i]->FitnessFunctionValue / totalValue) * 100;
		}
		// computing ranges attributable to each individual
		array<double> ^rangeEnds = gcnew array<double>(populationSize);
		rangeEnds[0] = percentages[0];
		for (int i = 1; i < populationSize; i++) {
			rangeEnds[i] = rangeEnds[i - 1] + percentages[i];
		}
		// draw of individuals for crossover
		array<Individual^> ^chosen = gcnew array<Individual^>(populationSize);
		for (int i = 0; i < populationSize; i++) {
			double randomNumber = (rand->Next(0,10000)) / 100;
			for (int j = 0; j < populationSize; j++) {
				if (randomNumber <= rangeEnds[j]) {
					// if random number is in the range of specific individual
					// it's data is prescribed to chosen individuals collection
					chosen[i] = individuals->PopulationMembers[j];
					break;
				}
				else if (j == populationSize - 1) {
					// if j == populationSize-1 and program executes here
					// it means that it did't find suitable range: error!
					throw gcnew System::Exception("Error in roulette selection! (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|selectParents)");
				}
			}
		}
		// moving chosen parent population into original individuals population
		for (int i = 0; i < populationSize; i++) {
			individuals->PopulationMembers[i] = gcnew Individual(chosen[i]);
		}
		break;
	}
	case selectionMethod::ranking: {

		// creating ranking of individuals with top 4 fitness function values
		array<Individual^> ^top4 = gcnew array<Individual^>(4);
		top4[0] = sorted[0];
		for (int i = 0; i < populationSize; i++) {
			if (sorted[i]->getEncodedValue() != top4[0]->getEncodedValue()) {
				top4[1] = sorted[i];
				for (int j = i; j < populationSize; j++) {
					if (sorted[j]->getEncodedValue() != top4[1]->getEncodedValue()) {
						top4[2] = sorted[j];
						for (int k = j; k < populationSize; k++) {
							if (sorted[k]->getEncodedValue() != top4[2]->getEncodedValue()) {
								top4[3] = sorted[k];
								break;
							}
							if (k == populationSize - 1) top4[3] = top4[2];
						}
						break;
					}
					if (j == populationSize - 1) top4[3] = top4[2] = top4[1];
				}
				break;
			}
			if (i == populationSize - 1) top4[3] = top4[2] = top4[1] = top4[0];
		}

		// creating chosen parent population
		if (populationSize % 10 != 0) { throw gcnew System::ArithmeticException("Invalid population size (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|selectParents)"); }
		array<Individual^> ^chosen = gcnew array<Individual^>(populationSize);
		// 1. in ranking gets 40% parent individuals
		for (int i = 0; i < 0.4*populationSize; i++) {
			chosen[i] = top4[0];
		}
		// 2. in ranking gets 30% parent individuals
		for (int i = static_cast<int>(0.4*populationSize); i < 0.7*populationSize; i++) {
			chosen[i] = top4[1];
		}
		// 3. in ranking gets 20% parent individuals
		for (int i = static_cast<int>(0.7*populationSize); i < 0.9*populationSize; i++) {
			chosen[i] = top4[2];
		}
		// 4. in ranking gets 10% parent individuals
		for (int i = static_cast<int>(0.9*populationSize); i < populationSize; i++) {
			chosen[i] = top4[3];
		}
		// scrambling individuals in chosen parent population
		// (chosing two random indexes and swaping individuals (populationSize)x times
		int randomIndex1 = 0, randomIndex2 = 0;
		for (int i = 0; i < populationSize; i++) {
			randomIndex1 = rand->Next(0,populationSize);
			do { randomIndex2 = rand->Next(0,populationSize); } while (randomIndex2 == randomIndex1);
			Individual^ temporary = chosen[randomIndex1];
			chosen[randomIndex1] = chosen[randomIndex2];
			chosen[randomIndex2] = temporary;
		}
		// moving chosen parent population into original individuals population
		for (int i = 0; i < populationSize; i++) {
			individuals->PopulationMembers[i] = gcnew Individual(chosen[i]);
		}
		break;
	}
	case selectionMethod::tournament: {

		array<Individual^> ^chosen = gcnew array<Individual^>(populationSize);
		int randIndex1 = 0, randIndex2 = 0, randIndex3 = 0;

		for (int i = 0; i < populationSize; i++) {
			// choosing three different random individuals
			randIndex1 = rand->Next(0,populationSize);
			do { randIndex2 = rand->Next(0,populationSize); } while (randIndex2 == randIndex1);
			do { randIndex3 = rand->Next(0,populationSize); } while (randIndex3 == randIndex1 || randIndex3 == randIndex2);
			// adding individual with highest fitness funtion value to chosen collection
			if (individuals->PopulationMembers[randIndex1]->FitnessFunctionValue >=
				individuals->PopulationMembers[randIndex2]->FitnessFunctionValue &&
				individuals->PopulationMembers[randIndex1]->FitnessFunctionValue >=
				individuals->PopulationMembers[randIndex3]->FitnessFunctionValue)
			{
				chosen[i] = individuals->PopulationMembers[randIndex1];
			}
			else if (individuals->PopulationMembers[randIndex2]->FitnessFunctionValue >=
				individuals->PopulationMembers[randIndex1]->FitnessFunctionValue &&
				individuals->PopulationMembers[randIndex2]->FitnessFunctionValue >=
				individuals->PopulationMembers[randIndex3]->FitnessFunctionValue)
			{
				chosen[i] = individuals->PopulationMembers[randIndex2];
			}
			else { // (individuals->PopulationMembers[randIndex3]->FitnessFunctionValue >=
				   // individuals->PopulationMembers[randIndex1]->FitnessFunctionValue &&
				   // individuals->PopulationMembers[randIndex3]->FitnessFunctionValue >=
				   // individuals->PopulationMembers[randIndex2]->FitnessFunctionValue)
				chosen[i] = individuals->PopulationMembers[randIndex3];
			}
		}
		// moving chosen parent population into original individuals population
		for (int i = 0; i < populationSize; i++) {
			individuals->PopulationMembers[i] = gcnew Individual(chosen[i]);
		}
		break;
	}
	default: { throw gcnew System::ArgumentException("Invalid selection method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|selectParents)"); break; }

	} // end of switch case

}

void GeneticAlgorythmToolbox::crossover(Population^ parents)
{

	switch (parents->InternalConfig->Flag_crossoverMethod) {

	case crossoverMethod::onePointCrossover: {

		// swaping genes in positions from locus to the end of genome
		int locus = 0;
		int indexBarrier = 0; // maximal index + 1

							  // grouping individuals in pairs
		for (int i = 0; i < parents->InternalConfig->PopulationSize; i += 2) {

			// conducting crossover with given probability
			if (rand->Next(0,100) < internalConfig->CrossoverProbability) {

				switch (parents->InternalConfig->Flag_codingMethod) {

				case codingMethod::binary8:
					locus = rand->Next(1,8); // index: 1-7
					indexBarrier = 8;
					break;
				case codingMethod::binary10:
					locus = rand->Next(1,10); // index: 1-9
					indexBarrier = 10;
					break;
				case codingMethod::integers:
					locus = rand->Next(1,4); // index: 1-3
					indexBarrier = 4;
					break;
				default:
					throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|crossover)");
					break;

				} // end of internal switch block

				// shifting genes
				array<char> ^buffer = gcnew array<char>(indexBarrier - locus);
				// writing genes from first parent genome into buffer
				int k = locus;
				for (int j = 0; j < (indexBarrier - locus); j++) {
					buffer[j] = parents->PopulationMembers[i]->Genome[k];
					k++;
				}
				// writing genes from second parent into first parent's genome
				for (k = locus; k < indexBarrier; k++) {
					parents->PopulationMembers[i]->Genome[k] = parents->PopulationMembers[i + 1]->Genome[k];
				}
				// writing genes from buffer into second parent's genome
				k = locus;
				for (int j = 0; j < (indexBarrier - locus); j++) {
					parents->PopulationMembers[i + 1]->Genome[k] = buffer[j];
					k++;
				}

			} // end of crossover conditional statement

		} // end of population loop

		break;
	}

	case crossoverMethod::twoPointCrossover: {

		// swaping genes in positiona from locusFront to locusBack
		int locusFront = 0;
		int locusBack = 0;

		// grouping individuals in pairs
		for (int i = 0; i < parents->InternalConfig->PopulationSize; i += 2) {

			// conducting crossover with given probability
			if (rand->Next(0,100) < internalConfig->CrossoverProbability) {

				switch (parents->InternalConfig->Flag_codingMethod) {

				case codingMethod::binary8:
					locusFront = rand->Next(1,8); // index: 1-7
					locusBack = rand->Next(locusFront,8); // index: locusFront-7
					break;
				case codingMethod::binary10:
					locusFront = rand->Next(1,10); // index: 1-9
					locusBack = rand->Next(locusFront,10); // index: locusFront-9
					break;
				case codingMethod::integers:
					locusFront = rand->Next(1, 4); // index: 1-3
					locusBack = rand->Next(locusFront,4); // index: locusFront-3
					break;
				default:
					throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|crossover)");
					break;

				} // end of internal switch block

				  // shifting genes
				array<char> ^buffer = gcnew array<char>(locusBack - locusFront + 1);
				// writing genes from first parent genome into buffer
				int k = locusFront;
				for (int j = 0; j < (locusBack - locusFront + 1); j++) {
					buffer[j] = parents->PopulationMembers[i]->Genome[k];
					k++;
				}
				// writing genes from second parent into first parent's genome
				for (k = locusFront; k <= locusBack; k++) {
					parents->PopulationMembers[i]->Genome[k] = parents->PopulationMembers[i + 1]->Genome[k];
				}
				// writing genes from buffer into second parent's genome
				k = locusFront;
				for (int j = 0; j < (locusBack - locusFront + 1); j++) {
					parents->PopulationMembers[i + 1]->Genome[k] = buffer[j];
					k++;
				}

			} // end of crossover conditional statement

		} // end of population loop

		break;
	}

	case crossoverMethod::uniformCrossover: {

		// grouping individuals in pairs
		for (int i = 0; i < parents->InternalConfig->PopulationSize; i += 2) {

			// conducting crossover with given probability
			if (rand->Next(0,100) < internalConfig->CrossoverProbability) {

				// determining genome length
				int genomeLength = 0;
				switch (parents->InternalConfig->Flag_codingMethod) {
				case codingMethod::binary8:
					genomeLength = 8;
					break;
				case codingMethod::binary10:
					genomeLength = 10;
					break;
				case codingMethod::integers:
					genomeLength = 4;
					break;
				default:
					throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|crossover)");
					break;
				}

				// creating maps of genes to swap
				array<bool> ^map = gcnew array<bool>(genomeLength);
				for (int j = 0; j < genomeLength; j++) {
					if (rand->Next(0,2) == 1) { map[j] = true; }
					else { map[j] = false; }
				}

				// swapping genes on position for which map[position] = true
				char buffer = ' ';
				for (int j = 0; j < genomeLength; j++) {
					if (map[j] == true) {
						buffer = parents->PopulationMembers[i]->Genome[j];
						parents->PopulationMembers[i]->Genome[j] = parents->PopulationMembers[i + 1]->Genome[j];
						parents->PopulationMembers[i + 1]->Genome[j] = buffer;
					}
				}

			} // end of crossover conditional statement

		} // end of population loop

		break;
	}

	case crossoverMethod::averaging: {

		if (parents->InternalConfig->Flag_codingMethod != codingMethod::integers) {
			throw gcnew System::InvalidOperationException("Cannot apply averaging to binary encoded genome (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|crossover)");
		}

		// grouping individuals in pairs
		for (int i = 0; i < parents->InternalConfig->PopulationSize; i += 2) {

			// conducting crossover with given probability
			if (rand->Next(0,100) < internalConfig->CrossoverProbability) {

				// averaging genes in positions from locus to the end of genome
				int locus = rand->Next(1,4); // index: 1-3

											  // averaging genes and writing them into genomes of parents
				char averagedGene = ' ';
				for (int k = locus; k < 4; k++) {
					averagedGene =
						static_cast<char>(
							static_cast<int>(
								System::Math::Round
								((parents->PopulationMembers[i]->Genome[k] +
									parents->PopulationMembers[i + 1]->Genome[k]) / 2)));
					parents->PopulationMembers[i]->Genome[k] = averagedGene;
					parents->PopulationMembers[i + 1]->Genome[k] = averagedGene;
				}

			} // end of crossover conditional statement

		} // end of population loop

		break;
	}

	default: {
		throw gcnew System::ArgumentException("Invalid crossover method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|crossover)");
		break;
	}

	} // end of switch block

}

void GeneticAlgorythmToolbox::mutate(Population^ individuals)
{

	switch (internalConfig->Flag_mutationMethod)
	{
	case mutationMethod::none:
		// do nothing
		break;

	case mutationMethod::geneNegation:

		switch (individuals->InternalConfig->Flag_codingMethod)
		{

		case codingMethod::binary8:
			for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {
				for (int j = 0; j < 8; j++)
				{
					// if random number is smaller or equal to mutation probability negate bit
					if (rand->Next(0,100) < internalConfig->MutationProbability) {
						if (individuals->PopulationMembers[i]->Genome[j] == static_cast<char>(1)) {
							individuals->PopulationMembers[i]->Genome[j] = static_cast<char>(0);
						}
						else { // (individuals->PopulationMembers[i]->Genome[j] == static_cast<char>(0))
							individuals->PopulationMembers[i]->Genome[j] = static_cast<char>(1);
						}
					}
				}
			}
			break;

		case codingMethod::binary10:

			for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {
				for (int j = 0; j < 10; j++)
				{
					// if random number is smaller or equalto mutation probability negate bit
					if (rand->Next(0,100) < internalConfig->MutationProbability) {
						if (individuals->PopulationMembers[i]->Genome[j] == static_cast<char>(1)) {
							individuals->PopulationMembers[i]->Genome[j] = static_cast<char>(0);
						}
						else { // (individuals->PopulationMembers[i]->Genome[j] == static_cast<char>(0))
							individuals->PopulationMembers[i]->Genome[j] = static_cast<char>(1);
						}
					}
				}
			}
			break;

		default:
			throw gcnew System::InvalidOperationException("Cannot apply gene negation mutation on integers (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|mutate)");
			break;
		}

		break;

	case mutationMethod::geneSwap:

		for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {

			int j1 = 0;
			int j2 = 0;

			// if random number is smaller or equal to mutation probability choose two random gen positions and swap genes
			if (rand->Next(0,100) < internalConfig->MutationProbability) {

				switch (individuals->InternalConfig->Flag_codingMethod)
				{

				case codingMethod::binary8:
					j1 = rand->Next(0,8);
					j2 = rand->Next(0,8);
					while (j2 == j1) { j2 = rand->Next(0,8); }
					break;

				case codingMethod::binary10:
					j1 = rand->Next(0,10);
					j2 = rand->Next(0,10);
					while (j2 == j1) { j2 = rand->Next(0,10); }
					break;

				case codingMethod::integers:
					j1 = rand->Next(0,4);
					j2 = rand->Next(0,4);
					while (j2 == j1) { j2 = rand->Next(0,4); }
					break;

				default:
					throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|mutate)");
					break;
				}

				// swapping genes on chosen positions
				char temporary = individuals->PopulationMembers[i]->Genome[j1];
				individuals->PopulationMembers[i]->Genome[j1] = individuals->PopulationMembers[i]->Genome[j2];
				individuals->PopulationMembers[i]->Genome[j2] = temporary;
			}

		}

		break;

	case mutationMethod::permutation:

		switch (individuals->InternalConfig->Flag_codingMethod)
		{

		case codingMethod::binary8:
			for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {

				int genesToPermuteQuantity = 0;
				char genesToPermute[8];
				int genesToPermuteIndexes[8];

				for (int j = 0; j < 8; j++)
				{
					// if random number is smaller or equal to mutation probability use gene in permutation
					if (rand->Next(0,100) < internalConfig->MutationProbability) {
						genesToPermute[genesToPermuteQuantity] = individuals->PopulationMembers[i]->Genome[j];
						genesToPermuteIndexes[genesToPermuteQuantity] = j;
						genesToPermuteQuantity++;
					}
				}

				permutate(genesToPermute, genesToPermuteQuantity);

				for (int k = 0; k < genesToPermuteQuantity; k++)
				{
					individuals->PopulationMembers[i]->Genome[genesToPermuteIndexes[k]] = genesToPermute[k];
				}
			}
			break;

		case codingMethod::binary10:

			for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {

				int genesToPermuteQuantity = 0;
				char genesToPermute[10];
				int genesToPermuteIndexes[10];

				for (int j = 0; j < 10; j++)
				{
					// if random number is smaller or equal to mutation probability use gene in permutation
					if (rand->Next(0,100) < internalConfig->MutationProbability) {
						genesToPermute[genesToPermuteQuantity] = individuals->PopulationMembers[i]->Genome[j];
						genesToPermuteIndexes[genesToPermuteQuantity] = j;
						genesToPermuteQuantity++;
					}
				}

				permutate(genesToPermute, genesToPermuteQuantity);

				for (int k = 0; k < genesToPermuteQuantity; k++)
				{
					individuals->PopulationMembers[i]->Genome[genesToPermuteIndexes[k]] = genesToPermute[k];
				}
			}
			break;

		case codingMethod::integers:

			for (int i = 0; i < individuals->InternalConfig->PopulationSize; i++) {

				int genesToPermuteQuantity = 0;
				char genesToPermute[4];
				int genesToPermuteIndexes[4];

				for (int j = 0; j < 4; j++)
				{
					// if random number is smaller or equal to mutation probability use gene in permutation
					if (rand->Next(0,100) < internalConfig->MutationProbability) {
						genesToPermute[genesToPermuteQuantity] = individuals->PopulationMembers[i]->Genome[j];
						genesToPermuteIndexes[genesToPermuteQuantity] = j;
						genesToPermuteQuantity++;
					}
				}

				permutate(genesToPermute, genesToPermuteQuantity);

				for (int k = 0; k < genesToPermuteQuantity; k++)
				{
					individuals->PopulationMembers[i]->Genome[genesToPermuteIndexes[k]] = genesToPermute[k];
				}
			}
			break;

		default:
			throw gcnew System::ArgumentException("Invalid coding method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|mutate)");
			break;
		}

		break;

	default:
		throw gcnew System::ArgumentException("Invalid mutation method (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|mutate)");
		break;
	}

}

void GeneticAlgorythmToolbox::applySelectionModification(Population^ individuals)
{
	// handling selection modifications
	int populationSize = individuals->InternalConfig->PopulationSize;
	int numberOfAutomaticallySelected = 0; // number of top individuals automatically selected to next generation population
	switch (internalConfig->Flag_selectionModification) {
	case selectionModification::none:
		break;
	case selectionModification::eliteSelection:
		numberOfAutomaticallySelected = 1; // the best individual gets to next generation
		break;
	case selectionModification::partialExchange:
		numberOfAutomaticallySelected = static_cast<int>(0.4 * populationSize); // 40% best individuals get to next generation
		break;
	default:
		throw gcnew System::ArgumentException("Invalid selection modification (GeneticAlgorythmEngine.cpp|GeneticAlgorythmToolbox|applySelectionMidification)");
		break;
	}
	// randomly inserting automatically selected individuals into given population
	// (using sorted array prepared in 'selectParents' internal method)
	for (int i = 0; i < numberOfAutomaticallySelected; i++) {
		individuals->PopulationMembers[rand->Next(0,populationSize)] = gcnew Individual(sorted[i]);
	}
}

double GeneticAlgorythmToolbox::computeParabolaValue(double argument)
{
	// function computes value for given argument
	return internalConfig->AFactor * System::Math::Pow(argument, 2) + internalConfig->BFactor * argument + internalConfig->CFactor;
}

void GeneticAlgorythmToolbox::permutate(char* genes, int quantity)
{
	// function permutes number of genes in given array
	// (used in mutate function for permutation mutation method)
	char* newOrder = new char[quantity];
	int randomIndex = 0;
	for (int i = 0; i < quantity; i++) { newOrder[i] = static_cast<char>(-1); }
	for (int i = 0; i < quantity; i++) {
		do { randomIndex = rand->Next(0,quantity); } while (newOrder[randomIndex] != static_cast<char>(-1));
		newOrder[randomIndex] = genes[i];
	}
	for (int i = 0; i < quantity; i++) {
		genes[i] = newOrder[i];
	}
	delete[] newOrder;
}

// --------------------------------------------------------------------------------------------------