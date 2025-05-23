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
			//  список данных
			dataList = gcnew List<PressureData^>();


			clickCount = 0;


			// инициализация других элементов
			dataList = gcnew List<PressureData^>();
			// другие инициализации




			dataGridView->Columns->Add("Type", "Тип");
			dataGridView->Columns->Add("Date", "Дата");
			dataGridView->Columns->Add("Height", "Высота");
			dataGridView->Columns->Add("Meaning", "Значение");
			dataGridView->Columns->Add("Salinity", "Соленость");
			//загружаем данные из файла
			LoadFromFile();
		}

	private:


		int clickCount;
		Label^ clickCounterLabel;


		// объявляются как указатели на объекты 
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


			// Инициализация метки для счетчика
			clickCounterLabel = gcnew Label();
			clickCounterLabel->Location = Drawing::Point(600, 250);
			clickCounterLabel->Size = Drawing::Size(100, 20);
			//clickCounterLabel->Text = "Нажатий: ";
			this->Controls->Add(clickCounterLabel);




			//gcnew выделяет память 
			this->dataGridView = gcnew DataGridView();
			this->typeComboBox = gcnew ComboBox();
			this->dateTextBox = gcnew TextBox();
			this->heightTextBox = gcnew TextBox();
			this->meaningTextBox = gcnew TextBox();
			this->salinityTextBox = gcnew TextBox();
			this->addButton = gcnew Button();

			//координаты, размеры и поведение элемента 
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

			this->addButton->Text = "Добавить";
			this->addButton->Location = Drawing::Point(480, 250);
			this->addButton->Click += gcnew EventHandler(this, &MyForm::addButton_Click);

			this->deleteButton = gcnew Button();
			this->deleteButton->Text = "Удалить выбранное";
			this->deleteButton->Location = Drawing::Point(480, 280);

			this->deleteButton->Click += gcnew EventHandler(this, &MyForm::deleteButton_Click);
			this->Controls->Add(deleteButton);

			Label^ dateLabel = gcnew Label();
			dateLabel->Text = "Дата:";
			dateLabel->Location = Drawing::Point(10, 250);
			this->Controls->Add(dateLabel);
			Label^ heightLabel = gcnew Label();
			heightLabel->Text = "Высота:";
			heightLabel->Location = Drawing::Point(120, 250);
			this->Controls->Add(heightLabel);
			Label^ meaningLabel = gcnew Label();
			meaningLabel->Text = "Значение:";
			meaningLabel->Location = Drawing::Point(230, 250);
			this->Controls->Add(meaningLabel);
			Label^ salinityLabel = gcnew Label();
			salinityLabel->Text = "Соленость:";
			salinityLabel->Location = Drawing::Point(340, 250);
			this->Controls->Add(salinityLabel);

			// отображение окна с кнопкамиц
			this->ClientSize = Drawing::Size(700, 400);
			this->Controls->Add(dataGridView);
			this->Controls->Add(typeComboBox);
			this->Controls->Add(dateTextBox);
			this->Controls->Add(heightTextBox);
			this->Controls->Add(meaningTextBox);
			this->Controls->Add(salinityTextBox);
			this->Controls->Add(addButton);
			this->Text = "Данные о давлении";

			this->saveButton = gcnew Button();
			this->saveButton->Text = "Сохранить";
			this->saveButton->Location = Drawing::Point(480, 310);
			this->saveButton->Click += gcnew EventHandler(this, &MyForm::saveButton_Click);
			this->Controls->Add(saveButton);

			this->openFileButton = gcnew Button();
			this->openFileButton->Text = "Открыть файл";
			this->openFileButton->Location = Drawing::Point(10, 310);
			this->openFileButton->Click += gcnew EventHandler(this, &MyForm::openFileButton_Click);
			this->Controls->Add(openFileButton);
			this->typeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::typeComboBox_SelectedIndexChanged);

		}



		void LoadFromFile(String^ path)
		{
			//marshal_as<std::string> превращает в string
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
				//создаем объект
				PressureData^ pd = gcnew PressureData(
					//обратно в систем стринг
					gcnew String(type.c_str()),
					gcnew String(date.c_str()),
					height,
					meaning,
					gcnew String(salinity.c_str())
				);
				//Добавляем запись в список и в таблицу DataGridView
				dataList->Add(pd);
				AddRowToGrid(pd);
			}
			file.close();
		}

		bool IsValidDate(String^ dateStr)
		{
			// Ожидаем формат "год.месяц.число", например: 2025.05.23
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

				// Можно добавить более сложную проверку для месяцев и високосных годов, но для простоты пока так

				return true;
			}
			catch (...)
			{
				return false; // Если не получилось конвертировать в int — невалидно
			}
		}

		void typeComboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e)
		{
			String^ selectedType = typeComboBox->SelectedItem->ToString();
			if (selectedType == "atm")
			{
				salinityTextBox->Text = "";           // очищаем поле
				salinityTextBox->Enabled = false;    // делаем поле недоступным для ввода
			}
			else if (selectedType == "under")
			{
				salinityTextBox->Enabled = true;     // делаем поле доступным
			}
		}

		void AddRowToGrid(PressureData^ obj)
		{
			//Эта функция добавляет строку с данными объекта в таблицу
			array<String^>^ row =
			{
				obj->Type,
				obj->Date,
				//превр в текст числа
				obj->Height.ToString(),
				obj->Meaning.ToString(),
				obj->Salinity
			};
			dataGridView->Rows->Add(row);
		}

		void AppendToFile(PressureData^ obj)
		{
			//добавляет объект в конец файла
			std::ofstream file("pressure.txt", std::ios::app);
			WriteObjectToStream(file, obj);
			file.close();
		}

		void WriteObjectToStream(std::ofstream& file, PressureData^ obj)
		{
			std::string line;
			if (obj->Type == "atm")
			{
				//из систем стринг в стринг
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
			//clickCounterLabel->Text = "Нажатий: " + clickCount.ToString();

			if (typeComboBox->SelectedItem == nullptr) {
				MessageBox::Show("Выберите тип", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
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
					throw gcnew Exception("Неверный формат даты. Ожидается 'год.месяц.число' с допустимыми значениями месяца (1-12) и дня (1-31).");
				}

				// Проверяем для типа "under", что значение солености корректно
				if (type == "under")
				{
					if (salinity != "Min" && salinity != "Medium" && salinity != "High")
					{
						throw gcnew Exception("Для типа 'under' значение солености должно быть: Min, Medium или High.");
					}
				}
				else
				{
					// Для типа "atm" очищаем соленость, как и раньше
					salinity = "";
				}

				double height = Convert::ToDouble(heightStr);
				int meaning = Convert::ToInt32(meaningStr);

				PressureData^ newObj = gcnew PressureData(type, date, height, meaning, salinity);
				dataList->Add(newObj);
				AddRowToGrid(newObj);

				MessageBox::Show("Объект добавлен", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка ввода: " + ex->Message);

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
					logFile << "[" << logDateTime << "] Ошибка при добавлении объекта: " << errorMsg << std::endl;
					logFile << "Введённые данные: Type='" << logType << "', Date='" << logDate << "', Height='"
						<< logHeight << "', Meaning='" << logMeaning << "', Salinity='" << logSalinity << "'" << std::endl;
					logFile << "--------------------------------------------------------" << std::endl;
					logFile.close();
				}
				catch (...) {
					// Игнорируем ошибки записи в лог
				}
			}
		}

		/*
		void addButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			clickCounterLabel->Text = "Нажатий: " + clickCount.ToString();

			//доюавляем объект в таблицу
			//проверка выбран ли тип
			if (typeComboBox->SelectedItem == nullptr) {
				MessageBox::Show("Выберите тип", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				// в строку
				String^ type = typeComboBox->SelectedItem->ToString();
				String^ date = dateTextBox->Text;
				//в double
				double height = Convert::ToDouble(heightTextBox->Text);
				int meaning = Convert::ToInt32(meaningTextBox->Text);
				String^ salinity = salinityTextBox->Text;

				if (type == "atm") salinity = "";

				PressureData^ newObj = gcnew PressureData(type, date, height, meaning, salinity);
				dataList->Add(newObj);
				AddRowToGrid(newObj);

				MessageBox::Show("Объект добавлен", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка ввода: " + ex->Message);
			}
		}
		*/


		void deleteButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			//clickCounterLabel->Text = "Нажатий: " + clickCount.ToString();

			//если не кликнули на строку
			if (dataGridView->SelectedRows->Count == 0) {
				MessageBox::Show("Выберите строку для удаления", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			int index = dataGridView->SelectedRows[0]->Index;
			if (index < 0 || index >= dataList->Count) return;
			// Удаляем из списка и из таблицы
			dataList->RemoveAt(index);
			dataGridView->Rows->RemoveAt(index);

			MessageBox::Show("Запись удалена", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void saveButton_Click(Object^ sender, EventArgs^ e)
		{

			clickCount++;
			//clickCounterLabel->Text = "Нажатий: " + clickCount.ToString();

			OverwriteFile();
			MessageBox::Show("Данные сохранены в файл", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void OverwriteFile()
		{
			//переход из систем стринг в стринг
			msclr::interop::marshal_context context;
			std::string filePath = context.marshal_as<std::string>(currentFilePath);
			//Это полностью очистит старое содержимое и создаст новое
			std::ofstream file(filePath);

			for each (PressureData ^ obj in dataList) {
				WriteObjectToStream(file, obj);
			}
			file.close();
		}

		void openFileButton_Click(Object^ sender, EventArgs^ e)
		{
			// увеличиваем счетчик нажатий
			clickCount++;
			//clickCounterLabel->Text = "Нажатий: " + clickCount.ToString();


			// диалоговое окно для открытия файла
			OpenFileDialog^ dialog = gcnew OpenFileDialog();
			//выбираем только txt
			dialog->Filter = "Text Files|*.txt|All Files|*.*";
			//выбран файл
			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// Записываем путь к выбранному файлу
				currentFilePath = dialog->FileName;
				//Очищаем таблицу
				dataGridView->Rows->Clear();
				dataList->Clear();
				//новые данные
				LoadFromFile(currentFilePath);
			}
		}

		//чтобы в начале данные записались из файла
		void LoadFromFile()
		{
			LoadFromFile(currentFilePath);
		}

	};
}