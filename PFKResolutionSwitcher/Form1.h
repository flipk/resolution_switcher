/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#pragma once

#include "myscreens.h"

namespace PFKResolutionSwitcher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1
	{
	private:
		allScreens ^ screens;
	public:
		Form1(void);

	protected:
		~Form1();

	private:
		System::Windows::Forms::NotifyIcon^  notifyIcon1;
		System::Void exitMenuClick(System::Object^  sender, System::EventArgs^  e);
	};
}
