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
	private:
		allScreens ^ screens;
	public:
		Form1(void);

	protected:
		~Form1();

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::NotifyIcon^  systemTrayIcon;
	private: System::Windows::Forms::Label^  selectModesLabel;
	private: System::Windows::Forms::Button^  buttonSave;
	private: System::Windows::Forms::Button^  buttonCancel;

	private: System::ComponentModel::IContainer^  components;

	private:

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
			this->systemTrayIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->selectModesLabel = (gcnew System::Windows::Forms::Label());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(25, 126);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(186, 117);
			this->textBox1->TabIndex = 0;
			// 
			// systemTrayIcon
			// 
			this->systemTrayIcon->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"systemTrayIcon.Icon")));
			this->systemTrayIcon->Text = L"PFKResolutionSwitcher";
			this->systemTrayIcon->Visible = true;
			this->systemTrayIcon->Click += gcnew System::EventHandler(this, &Form1::systemTrayIcon_Click);
			// 
			// selectModesLabel
			// 
			this->selectModesLabel->AutoSize = true;
			this->selectModesLabel->Location = System::Drawing::Point(12, 9);
			this->selectModesLabel->Name = L"selectModesLabel";
			this->selectModesLabel->Size = System::Drawing::Size(175, 13);
			this->selectModesLabel->TabIndex = 1;
			this->selectModesLabel->Text = L"Select all modes to appear in menu:";
			// 
			// buttonSave
			// 
			this->buttonSave->Location = System::Drawing::Point(25, 58);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(75, 23);
			this->buttonSave->TabIndex = 11;
			this->buttonSave->Text = L"Save";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &Form1::buttonSave_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(106, 58);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 12;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &Form1::buttonCancel_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(306, 326);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->selectModesLabel);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form1";
			this->Text = L"PFKResolutionSwitcher Configuration";
			this->Load += gcnew System::EventHandler(this, &Form1::myLoadEvent);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
System::Void myLoadEvent(System::Object^  sender, System::EventArgs^  e);
System::Void systemTrayIcon_Click(System::Object^  sender, System::EventArgs^  e);
System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e);
System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e);
};
}
