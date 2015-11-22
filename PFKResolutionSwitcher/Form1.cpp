/* -*- Mode:c++; eval:(c-set-style "BSD"); c-basic-offset:4; indent-tabs-mode:t; tab-width:4 -*- */

#include "stdafx.h"
#include "Form1.h"

using namespace PFKResolutionSwitcher;
using namespace System;
using namespace System::Collections;


Form1::Form1(void)
{
	System::Windows::Forms::MenuItem ^ item;
	System::ComponentModel::ComponentResourceManager^  resources;
	System::Windows::Forms::MenuItem::MenuItemCollection ^ menu;

	notifyIcon1 = gcnew System::Windows::Forms::NotifyIcon;
	notifyIcon1->ContextMenu = gcnew System::Windows::Forms::ContextMenu;
	menu = notifyIcon1->ContextMenu->MenuItems;
	notifyIcon1->BalloonTipText = L"PFK Resolution Switcher";
	resources = gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid);
	notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon1.Icon")));
	notifyIcon1->Text = L"PFK Resolution Switcher";
	notifyIcon1->Visible = true;
	screens = gcnew allScreens;
	for each (aScreen ^ scr in screens->screens)
	{
		item = gcnew System::Windows::Forms::MenuItem;
		item->Text = scr->name;
		menu->Add(item);
		for each (aScreenMode ^ mode in scr->modes)
		{
			item = gcnew System::Windows::Forms::MenuItem;
			item->Text = mode->getInfo();
			mode->form1 = this;
			item->Click += gcnew System::EventHandler(mode, &aScreenMode::btnClicked);
			menu->Add(item);
		}
	}
	item = gcnew System::Windows::Forms::MenuItem;
	item->Click += gcnew System::EventHandler(this, &Form1::exitMenuClick);
	item->Text = L"Exit";
	menu->Add(item);
}

Form1::~Form1()
{
	if (notifyIcon1)
		delete notifyIcon1;
	if (screens)
		delete screens;
}

System::Void
Form1::exitMenuClick(System::Object^  sender, System::EventArgs^  e)
{
	if (notifyIcon1)
		delete notifyIcon1;
	notifyIcon1 = nullptr;
	if (screens)
		delete screens;
	screens = nullptr;
	Application::Exit();
}
