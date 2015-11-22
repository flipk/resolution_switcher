// PFKResolutionSwitcher.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

using namespace PFKResolutionSwitcher;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Form1 ^ f1 = gcnew Form1;
	Application::Run();
	return 0;
}
