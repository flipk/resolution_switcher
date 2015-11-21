/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#include "stdafx.h"
#include "Form1.h"

using namespace PFKResolutionSwitcher;
using namespace System;
using namespace System::Collections;


Form1::Form1(void)
{
	InitializeComponent();
	screens = gcnew allScreens;
}

Form1::~Form1()
{
	if (components)
	{
		delete components;
		delete screens;
	}
}

System::Void Form1::myLoadEvent(System::Object^  sender, System::EventArgs^  e)
{
	int start_X = 30;
	int start_Y = 40;
	int delta_X = 125;
	int delta_Y = 25;
	int X = start_X, Y = start_Y;
	int largest_Y = Y;

	this->Visible = false;
	this->SuspendLayout();
	for each (aScreen ^ scr in screens->screens)
	{
		Y = start_Y;
		System::Windows::Forms::Label ^ lbl =
			gcnew System::Windows::Forms::Label;
		lbl->AutoSize = true;
		lbl->Location = System::Drawing::Point(X, Y);
		lbl->Text = scr->name;
		this->Controls->Add(lbl);
		Y += delta_Y;
		if (Y > largest_Y)
			largest_Y = Y;
		for each (aScreenMode ^ mode in scr->modes)
		{
			System::Windows::Forms::Button ^ btn =
				gcnew System::Windows::Forms::Button;
			btn->Location = System::Drawing::Point(X + 20, Y);
			btn->Text = mode->getInfo();
			btn->UseVisualStyleBackColor = true;

			mode->form1 = this;
			btn->Click +=
				gcnew System::EventHandler(mode, &aScreenMode::btnClicked);

			this->Controls->Add(btn);
			Y += delta_Y;
			if (Y > largest_Y)
				largest_Y = Y;
			mode->btnMode = btn;
		}
		X += delta_X;
	}
	largest_Y += 20;
	largest_Y += 30;
	X += delta_X;
	largest_Y += 40;
	this->Size = System::Drawing::Size(X, largest_Y);

	this->ResumeLayout(false);
	this->PerformLayout();
}

System::Void
Form1::notifyIconClicked(System::Object^  sender,
							System::EventArgs^  e)
{
	this->Visible = true;
}

System::Void
Form1::hideButtonClicked(System::Object^  sender, System::EventArgs^  e)
{
	this->Visible = false;
}

System::Void
Form1::exitButtonClicked(System::Object^  sender, System::EventArgs^  e)
{
	Application::Exit();
}
