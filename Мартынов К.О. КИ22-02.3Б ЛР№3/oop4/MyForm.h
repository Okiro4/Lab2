#pragma once

#include <fstream>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <iostream>

namespace PressureApp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	//using namespace std;

	public ref class PressureData
	{
	public:
		//gs
		property String^ Type;
		property String^ Date;
		property double Height;
		property int Meaning;
		property String^ Salinity;

		PressureData(String^ type, String^ date, double height, int meaning, String^ salinity)
		{
			Type = type;
			Date = date;
			Height = height;
			Meaning = meaning;
			Salinity = salinity;
		}
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//  ������ ������
			dataList = gcnew List<PressureData^>();


			clickCount = 0;


			// ������������� ������ ���������
			dataList = gcnew List<PressureData^>();
			// ������ �������������




			dataGridView->Columns->Add("Type", "���");
			dataGridView->Columns->Add("Date", "����");
			dataGridView->Columns->Add("Height", "������");
			dataGridView->Columns->Add("Meaning", "��������");
			dataGridView->Columns->Add("Salinity", "���������");
			//��������� ������ �� �����
			LoadFromFile();
		}

	private:


		int clickCount;
		Label^ clickCounterLabel;


		// ����������� ��� ��������� �� ������� 
		List<PressureData^>^ dataList;
		System::Windows::Forms::DataGridView^ dataGridView;
		System::Windows::Forms::ComboBox^ typeComboBox;
		System::Windows::Forms::TextBox^ dateTextBox;
		System::Windows::Forms::TextBox^ heightTextBox;
		System::Windows::Forms::TextBox^ meaningTextBox;
		System::Windows::Forms::TextBox^ salinityTextBox;
		System::Windows::Forms::Button^ addButton;
		System::Windows::Forms::Button^ deleteButton;
		System::Windows::Forms::Button^ saveButton;
		System::Windows::Forms::Button^ openFileButton;
		String^ currentFilePath = "pressure.txt";

		void InitializeComponent(void)
		{


			// ������������� ����� ��� ��������
			clickCounterLabel = gcnew Label();
			clickCounterLabel->Location = Drawing::Point(600, 250);
			clickCounterLabel->Size = Drawing::Size(100, 20);
			//clickCounterLabel->Text = "�������: ";
			this->Controls->Add(clickCounterLabel);




			//gcnew �������� ������ 
			this->dataGridView = gcnew DataGridView();
			this->typeComboBox = gcnew ComboBox();
			this->dateTextBox = gcnew TextBox();
			this->heightTextBox = gcnew TextBox();
			this->meaningTextBox = gcnew TextBox();
			this->salinityTextBox = gcnew TextBox();
			this->addButton = gcnew Button();

			//����������, ������� � ��������� �������� 
			this->dataGridView->Location = Drawing::Point(10, 10);
			this->dataGridView->Size = Drawing::Size(580, 200);
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->ReadOnly = true;

			this->typeComboBox->Location = Drawing::Point(10, 220);
			this->typeComboBox->Items->AddRange(gcnew cli::array<Object^>{ "atm", "under" });

			this->dateTextBox->Location = Drawing::Point(10, 275);

			this->heightTextBox->Location = Drawing::Point(120, 275);

			this->meaningTextBox->Location = Drawing::Point(230, 275);

			this->salinityTextBox->Location = Drawing::Point(340, 275);
			this->salinityTextBox->Width = 120;

			this->addButton->Text = "��������";
			this->addButton->Location = Drawing::Point(480, 250);
			this->addButton->Click += gcnew EventHandler(this, &MyForm::addButton_Click);

			this->deleteButton = gcnew Button();
			this->deleteButton->Text = "������� ���������";
			this->deleteButton->Location = Drawing::Point(480, 280);

			this->deleteButton->Click += gcnew EventHandler(this, &MyForm::deleteButton_Click);
			this->Controls->Add(deleteButton);

			Label^ dateLabel = gcnew Label();
			dateLabel->Text = "����:";
			dateLabel->Location = Drawing::Point(10, 250);
			this->Controls->Add(dateLabel);
			Label^ heightLabel = gcnew Label();
			heightLabel->Text = "������:";
			heightLabel->Location = Drawing::Point(120, 250);
			this->Controls->Add(heightLabel);
			Label^ meaningLabel = gcnew Label();
			meaningLabel->Text = "��������:";
			meaningLabel->Location = Drawing::Point(230, 250);
			this->Controls->Add(meaningLabel);
			Label^ salinityLabel = gcnew Label();
			salinityLabel->Text = "���������:";
			salinityLabel->Location = Drawing::Point(340, 250);
			this->Controls->Add(salinityLabel);

			// ����������� ���� � ���������
			this->ClientSize = Drawing::Size(700, 400);
			this->Controls->Add(dataGridView);
			this->Controls->Add(typeComboBox);
			this->Controls->Add(dateTextBox);
			this->Controls->Add(heightTextBox);
			this->Controls->Add(meaningTextBox);
			this->Controls->Add(salinityTextBox);
			this->Controls->Add(addButton);
			this->Text = "������ � ��������";

			this->saveButton = gcnew Button();
			this->saveButton->Text = "���������";
			this->saveButton->Location = Drawing::Point(480, 310);
			this->saveButton->Click += gcnew EventHandler(this, &MyForm::saveButton_Click);
			this->Controls->Add(saveButton);

			this->openFileButton = gcnew Button();
			this->openFileButton->Text = "������� ����";
			this->openFileButton->Location = Drawing::Point(10, 310);
			this->openFileButton->Click += gcnew EventHandler(this, &MyForm::openFileButton_Click);
			this->Controls->Add(openFileButton);
			this->typeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::typeComboBox_SelectedIndexChanged);

		}



		void LoadFromFile(String^ path)
		{
			//marshal_as<std::string> ���������� � string
			std::ifstream file(msclr::interop::marshal_as<std::string>(path));

			std::string line;
			while (std::getline(file, line)) {
				std::istringstream ss(line);
				std::string type, date;
				double height;
				int meaning;
				std::string salinity;

				ss >> type >> date >> height >> meaning;

				if (type == "under")
				{
					std::getline(ss, salinity, '"');
					std::getline(ss, salinity, '"');
				}
				//������� ������
				PressureData^ pd = gcnew PressureData(
					//������� � ������ ������
					gcnew String(type.c_str()),
					gcnew String(date.c_str()),
					height,
					meaning,
					gcnew String(salinity.c_str())
				);
				//��������� ������ � ������ � � ������� DataGridView
				dataList->Add(pd);
				AddRowToGrid(pd);
			}
			file.close();
		}

		bool IsValidDate(String^ dateStr)
		{
			// ������� ������ "���.�����.�����", ��������: 2025.05.23
			array<String^>^ parts = dateStr->Split('.');

			if (parts->Length != 3)
				return false;

			try
			{
				int year = Convert::ToInt32(parts[0]);
				int month = Convert::ToInt32(parts[1]);
				int day = Convert::ToInt32(parts[2]);

				if (year < 1970 || year > 2025)
					return false;
				if (month < 1 || month > 12)
					return false;

				if (day < 1 || day > 31)
					return false;

				// ����� �������� ����� ������� �������� ��� ������� � ���������� �����, �� ��� �������� ���� ���

				return true;
			}
			catch (...)
			{
				return false; // ���� �� ���������� �������������� � int � ���������
			}
		}

		void typeComboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e)
		{
			String^ selectedType = typeComboBox->SelectedItem->ToString();
			if (selectedType == "atm")
			{
				salinityTextBox->Text = "";           // ������� ����
				salinityTextBox->Enabled = false;    // ������ ���� ����������� ��� �����
			}
			else if (selectedType == "under")
			{
				salinityTextBox->Enabled = true;     // ������ ���� ���������
			}
		}

		void AddRowToGrid(PressureData^ obj)
		{
			//��� ������� ��������� ������ � ������� ������� � �������
			array<String^>^ row =
			{
				obj->Type,
				obj->Date,
				//����� � ����� �����
				obj->Height.ToString(),
				obj->Meaning.ToString(),
				obj->Salinity
			};
			dataGridView->Rows->Add(row);
		}

		void AppendToFile(PressureData^ obj)
		{
			//��������� ������ � ����� �����
			std::ofstream file("pressure.txt", std::ios::app);
			WriteObjectToStream(file, obj);
			file.close();
		}

		void WriteObjectToStream(std::ofstream& file, PressureData^ obj)
		{
			std::string line;
			if (obj->Type == "atm")
			{
				//�� ������ ������ � ������
				line = msclr::interop::marshal_as<std::string>(obj->Type) + " "
					+ msclr::interop::marshal_as<std::string>(obj->Date) + " "
					+ std::to_string(obj->Height) + " "
					+ std::to_string(obj->Meaning);
			}
			else {
				line = msclr::interop::marshal_as<std::string>(obj->Type) + " "
					+ msclr::interop::marshal_as<std::string>(obj->Date) + " "
					+ std::to_string(obj->Height) + " "
					+ std::to_string(obj->Meaning) + " "
					+ "\"" + msclr::interop::marshal_as<std::string>(obj->Salinity) + "\"";
			}
			file << line << std::endl;
		}


		void addButton_Click(Object^ sender, EventArgs^ e)
		{
			clickCount++;
			//clickCounterLabel->Text = "�������: " + clickCount.ToString();

			if (typeComboBox->SelectedItem == nullptr) {
				MessageBox::Show("�������� ���", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ type = typeComboBox->SelectedItem->ToString();
			String^ date = dateTextBox->Text;
			String^ heightStr = heightTextBox->Text;
			String^ meaningStr = meaningTextBox->Text;
			String^ salinity = salinityTextBox->Text;

			try {
				if (!IsValidDate(date))
				{
					throw gcnew Exception("�������� ������ ����. ��������� '���.�����.�����' � ����������� ���������� ������ (1-12) � ��� (1-31).");
				}

				// ��������� ��� ���� "under", ��� �������� ��������� ���������
				if (type == "under")
				{
					if (salinity != "Min" && salinity != "Medium" && salinity != "High")
					{
						throw gcnew Exception("��� ���� 'under' �������� ��������� ������ ����: Min, Medium ��� High.");
					}
				}
				else
				{
					// ��� ���� "atm" ������� ���������, ��� � ������
					salinity = "";
				}

				double height = Convert::ToDouble(heightStr);
				int meaning = Convert::ToInt32(meaningStr);

				PressureData^ newObj = gcnew PressureData(type, date, height, meaning, salinity);
				dataList->Add(newObj);
				AddRowToGrid(newObj);

				MessageBox::Show("������ ��������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("������ �����: " + ex->Message);

				try {
					String^ dateTimeNow = DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss");

					std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
					std::string logDateTime = msclr::interop::marshal_as<std::string>(dateTimeNow);
					std::string logType = msclr::interop::marshal_as<std::string>(type);
					std::string logDate = msclr::interop::marshal_as<std::string>(date);
					std::string logHeight = msclr::interop::marshal_as<std::string>(heightStr);
					std::string logMeaning = msclr::interop::marshal_as<std::string>(meaningStr);
					std::string logSalinity = msclr::interop::marshal_as<std::string>(salinity);

					std::ofstream logFile("log.txt", std::ios::app);
					logFile << "[" << logDateTime << "] ������ ��� ���������� �������: " << errorMsg << std::endl;
					logFile << "�������� ������: Type='" << logType << "', Date='" << logDate << "', Height='"
						<< logHeight << "', Meaning='" << logMeaning << "', Salinity='" << logSalinity << "'" << std::endl;
					logFile << "--------------------------------------------------------" << std::endl;
					logFile.close();
				}
				catch (...) {
					// ���������� ������ ������ � ���
				}
			}
		}

		/*
		void addButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			clickCounterLabel->Text = "�������: " + clickCount.ToString();

			//��������� ������ � �������
			//�������� ������ �� ���
			if (typeComboBox->SelectedItem == nullptr) {
				MessageBox::Show("�������� ���", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				// � ������
				String^ type = typeComboBox->SelectedItem->ToString();
				String^ date = dateTextBox->Text;
				//� double
				double height = Convert::ToDouble(heightTextBox->Text);
				int meaning = Convert::ToInt32(meaningTextBox->Text);
				String^ salinity = salinityTextBox->Text;

				if (type == "atm") salinity = "";

				PressureData^ newObj = gcnew PressureData(type, date, height, meaning, salinity);
				dataList->Add(newObj);
				AddRowToGrid(newObj);

				MessageBox::Show("������ ��������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("������ �����: " + ex->Message);
			}
		}
		*/


		void deleteButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			//clickCounterLabel->Text = "�������: " + clickCount.ToString();

			//���� �� �������� �� ������
			if (dataGridView->SelectedRows->Count == 0) {
				MessageBox::Show("�������� ������ ��� ��������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			int index = dataGridView->SelectedRows[0]->Index;
			if (index < 0 || index >= dataList->Count) return;
			// ������� �� ������ � �� �������
			dataList->RemoveAt(index);
			dataGridView->Rows->RemoveAt(index);

			MessageBox::Show("������ �������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void saveButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			//clickCounterLabel->Text = "�������: " + clickCount.ToString();

			OverwriteFile();
			MessageBox::Show("������ ��������� � ����", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void OverwriteFile()
		{
			//������� �� ������ ������ � ������
			msclr::interop::marshal_context context;
			std::string filePath = context.marshal_as<std::string>(currentFilePath);
			//��� ��������� ������� ������ ���������� � ������� �����
			std::ofstream file(filePath);

			for each (PressureData ^ obj in dataList) {
				WriteObjectToStream(file, obj);
			}
			file.close();
		}

		void openFileButton_Click(Object^ sender, EventArgs^ e)
		{
			// ����������� ������� �������
			clickCount++;
			//clickCounterLabel->Text = "�������: " + clickCount.ToString();


			// ���������� ���� ��� �������� �����
			OpenFileDialog^ dialog = gcnew OpenFileDialog();
			//�������� ������ txt
			dialog->Filter = "Text Files|*.txt|All Files|*.*";
			//������ ����
			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// ���������� ���� � ���������� �����
				currentFilePath = dialog->FileName;
				//������� �������
				dataGridView->Rows->Clear();
				dataList->Clear();
				//����� ������
				LoadFromFile(currentFilePath);
			}
		}

		//����� � ������ ������ ���������� �� �����
		void LoadFromFile()
		{
			LoadFromFile(currentFilePath);
		}

	};
}