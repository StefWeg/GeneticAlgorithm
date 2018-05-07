// Genetic Algorythm.cpp : main project file.
// more information about program functionality in Documentation.txt

#include "stdafx.h"

#include "InterfaceForm.h"

using namespace GeneticAlgorythm;

[STAThread]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceForm());

	return 0;
}
