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

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			for each (Screen ^screen in Screen::AllScreens)
			{
				textBox1->Text += "screen: " + screen->DeviceName + "\r\n";
				textBox1->Text += "Bounds: " + screen->Bounds.ToString() + "\r\n";
			}
			int ind;
			bool done = false;
			for (ind = 0; !done;ind++)
			{
				aScreen ^ scr = aScreen::getScreen(ind);
				if (scr->name)
					textBox1->Text += "ascreen result : " + scr->getinfo() + "\r\n";
				else
					done = true;
				delete scr;
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(663, 468);
			this->textBox1->TabIndex = 0;
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon1.Icon")));
			this->notifyIcon1->Text = L"notifyIcon1";
			this->notifyIcon1->Visible = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(687, 492);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	};
}

