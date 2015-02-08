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
	textBox1->Text += screens->getInfo();
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
	int delta_Y = 20;
	int X = start_X, Y = start_Y;
	int largest_Y = Y;

	this->Visible = false;
	this->SuspendLayout();
	for each (aScreen ^ scr in screens->screens)
	{
		Y = start_Y;
		System::Windows::Forms::Label ^ lbl = gcnew System::Windows::Forms::Label;
		lbl->AutoSize = true;
		lbl->Location = System::Drawing::Point(X, Y);
		lbl->Text = scr->name;
		this->Controls->Add(lbl);
		Y += delta_Y;
		if (Y > largest_Y)
			largest_Y = Y;
		scr->labelMonitor = lbl;
		for each (aScreenMode ^ mode in scr->modes)
		{
			System::Windows::Forms::CheckBox ^ cb =
				gcnew System::Windows::Forms::CheckBox;
			cb->AutoSize = true;
			cb->Location = System::Drawing::Point(X + 20, Y);
			cb->Text = mode->getInfo();
			cb->UseVisualStyleBackColor = true;
			this->Controls->Add(cb);
			Y += delta_Y;
			if (Y > largest_Y)
				largest_Y = Y;
			mode->checkBoxMode = cb;
		}
		X += delta_X;
	}
	largest_Y += 20;
	this->buttonSave->Location = System::Drawing::Point(X/2-80, largest_Y);
	this->buttonCancel->Location = System::Drawing::Point(X/2+5, largest_Y);
	largest_Y += 30;
	X += delta_X;
	this->textBox1->Location = System::Drawing::Point(10, largest_Y);
	this->textBox1->Size = System::Drawing::Size(X-20, 220);
	largest_Y += 40;
	this->Size = System::Drawing::Size(X, largest_Y + 220);

	this->systemTrayIcon->ContextMenu =
		gcnew System::Windows::Forms::ContextMenu;

	this->systemTrayIcon->ContextMenu->MenuItems->Add("Exit");

	this->ResumeLayout(false);
	this->PerformLayout();
}

System::Void
Form1::systemTrayIcon_Click(System::Object^  sender,
							System::EventArgs^  e)
{
	this->Visible = true;
}

System::Void
Form1::buttonSave_Click(System::Object^  sender,
						System::EventArgs^  e)
{
	this->systemTrayIcon->ContextMenu->MenuItems->Clear();
	for each (aScreen ^ scr in screens->screens)
	{
		for each (aScreenMode ^ mode in scr->modes)
		{
			System::Windows::Forms::MenuItem ^ it;
			if (mode->checkBoxMode->Checked)
			{
				it = gcnew System::Windows::Forms::MenuItem(
					mode->screen->name + "  " + mode->name);
				this->systemTrayIcon->ContextMenu->MenuItems->Add(it);
			}
		}
	}
	this->systemTrayIcon->ContextMenu->MenuItems->Add("Exit");
}

System::Void
Form1::buttonCancel_Click(System::Object^  sender,
						  System::EventArgs^  e)
{
	this->Visible = false;
}
