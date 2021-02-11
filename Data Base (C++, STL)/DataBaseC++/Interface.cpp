#include "Interface.h"

//Доп. функции для работы

void loadScreen(const unsigned int time, unsigned int count, const char symbol) { //останавливает поток на некоторое время и выводит опр. символы на консоль
	std::cout << "\t";
	while (count--) {
		std::cout << symbol << " ";
		Sleep(time);
	}
}

//Создание строки из n пробелов
void CreateTabulateString(std::string& text, size_t n) {
	text.clear();
	for (size_t i = 0; i < n; i++)
		text += " ";
}

int Absolute(int value) {
	return (value > 0) ? value : -value;
}

//Получить число(правильный ввод)

template<typename T>
T getCorrectValue(bool flag = false, T min = 0, T max = 0) {
	if (std::string(typeid(T).name()) == std::string(typeid(bool).name()))
		return T(0);

	T value = 0;
	if (min > max)
		std::swap(min, max);
	while ((!(std::cin >> value)) || (std::cin.bad())
		|| ((flag) && ((value < min) || (value > max)))) {
		if (flag) {
			std::cout << "Введите корректное число из диапазона " << "[ " << min << " ; " << max << " ] "
				<< " (тип: " << std::string(typeid(T).name()) + " ) : ";
		}
		else {
			std::cout << "Введите корректное число (тип " + std::string(typeid(T).name()) + " ): ";
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return value;
}

Interface::Interface() {}

Interface::Interface(std::string path) {
	setlocale(LC_ALL, "rus");
	try {
		if (!sData.LoadDataBase(path))
			throw std::string("Ошибка: не удалось загрузить данные из файла.\n");
	}
	catch (const std::string& error) {
		std::copy(error.begin(), error.end(), std::ostream_iterator<char>(std::cout));
		exit(-1);
	}

	(*this).sData.DataStringTable(&((*this).sDataTable));
	(*this).sDataColumn = (*this).sData.GetColumn();
}

void Interface::OutputData(std::string tabulate, const bool type) const {
	setlocale(LC_ALL, "rus");
	if (sDataColumn.size() <= 0) {
		std::cout << "Ошибка: база данных пуста.\n";
		return;
	}

	std::vector<int> max;
	for (size_t i = 0; i < sDataColumn.size(); i++) {
		if (type)
			max.push_back(sDataColumn[i].name.size() + 1 + sDataColumn[i].type.size() + tabulate.size());
		else
			max.push_back(sDataColumn[i].name.size() + tabulate.size());
	}

	for(size_t i = 0; i < sDataTable.size(); i++)
		for (size_t j = 0; j < sDataTable[i].size(); j++) {
			int value = (sDataTable[i][j].size() + tabulate.size());
			if (value > max[j])
				max[j] = value;
		}

	for (size_t i = 0; i < sDataColumn.size(); i++) {
		if (type) {
			CreateTabulateString(tabulate, max[i] - (sDataColumn[i].name.size() + 1 + sDataColumn[i].type.size()));
			std::cout << sDataColumn[i].name + ":" + sDataColumn[i].type << tabulate;
		}
		else {
			CreateTabulateString(tabulate, max[i] - sDataColumn[i].name.size());
			std::cout << sDataColumn[i].name << tabulate;
		}
	}
	std::cout << std::endl << std::endl;

	for (size_t i = 0; i < sDataTable.size(); i++) {
		for (size_t j = 0; j < sDataTable[i].size(); j++) {
			CreateTabulateString(tabulate, Absolute(max[j] - (sDataTable[i][j].size())));
			std::cout << sDataTable[i][j] << tabulate;
		}
		std::cout << std::endl;
	}
}

void Interface::CreateTable() {
	setlocale(LC_ALL, "rus");
	sDataColumn.clear();
	sDataTable.clear();
	std::cout << "Введите название базы данных: ";
	std::string name = "";
	std::getline(std::cin, name);

	std::cout << "Введите число столбцов: ";
	size_t n_column = getCorrectValue<size_t>(true, 0, 50);

	std::vector<DataColumn> columns(n_column);

	for (size_t i = 0; i < n_column; i++) {
		/*std::string text = "Введите имя " + std::string(itoa(i, nullptr, 10));
		std::copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout, " "));*/
		std::cout << "Введите название " << (i + 1) << "-го столбца: ";
		std::getline(std::cin, columns[i].name);
		std::cout << "Введите тип(int, double, string) " << (i + 1) << "-го столбца: ";
		std::getline(std::cin, columns[i].type);
		/*if ((columns[i].type != Data::intType)
			&& (columns[i].type != Data::doubleType)
			&& (columns[i].type != Data::stringType)) {
			std::cout << "Ошибка: введён не корректный тип столбца. Тип должен быть из 3-х доступных: int, double и string.\n";
			return;
		}*/
	}

	if (!sData.CreateTable(name, columns)) {
		std::cout << "Ошибка: введён не корректный тип столбца. Тип должен быть из 3-х доступных: int, double и string.\n";
		return;
	}

	(*this).sData.DataStringTable(&((*this).sDataTable));
	(*this).sDataColumn = (*this).sData.GetColumn();
}

void Interface::InsertData() {
	setlocale(LC_ALL, "rus");
	if (!sData.isTable()) {
		std::cout << "Ошибка: нельзя ввести данные в несуществующую таблицу.\n\n";
		return;
	}

	std::vector<std::string> data(sDataColumn.size());
	for (size_t i = 0; i < data.size(); i++) {
		std::cout << "Введите данные в столбец ( " << (i+1) << " ) " << sDataColumn[i].name + ":" + sDataColumn[i].type << " = ";
		std::getline(std::cin, data[i]);
		std::cout << std::endl;
	}

	if (!sData.DataStringTable(nullptr, &data)) {
		std::cout << "Ошибка: введённые данные не корректны (ошибка типов)." << std::endl;
		return;
	}
	
	(*this).sData.DataStringTable(&((*this).sDataTable));
}

void Interface::MenuInterface() {
	setlocale(LC_ALL, "rus");
	while (true) {
		system("cls");
		std::cout << "\t\tМеню" << std::endl << std::endl;
		std::cout << "1. Создание базы данных\n";
		std::cout << "2. Добавление данных\n";
		std::cout << "3. Удаление строки\n";
		std::cout << "4. Сохранение\n";
		std::cout << "5. Загрузка\n";
		std::cout << "6. Вывод базы данных на консоль\n";
		std::cout << "7. Выход из пользовательского интерфейса\n";
		std::cout << "Ваш выбор: ";
		int sw = getCorrectValue<int>(true, 1, 9);
		if (sw == 7)
			break;
		system("cls");

		switch (sw) {
		case 1: {
			(*this).CreateTable();
			std::cout << "\nБаза данных создана\n";
			loadScreen();
			break;
		}
		case 2: {
			bool next = false;
			do {
				system("cls");
				(*this).InsertData();

				std::cout << "Продолжить ввод данных? (0 - нет, 1 - да): ";
				next = (bool)getCorrectValue<int>(true, 0, 1);
			} while (next);
			std::cout << "\nВвод данных завершён\n";
			loadScreen();
			break;
		}
		case 3: {
			size_t numberString = 0;
			std::cout << "\nВведите номер строки таблицы для удаления (от 1 до " << (*this).sData.GetTableSize() << " ) : ";
			numberString = getCorrectValue<size_t>(true, 1, (*this).sData.GetTableSize());
			(*this).sData.DeleteStringTable(numberString - 1);
			std::cout << "\nСтрока таблицы удалена\n";
			(*this).sData.DataStringTable(&((*this).sDataTable));
			loadScreen();
			break;
		}
		case 4: {
			std::cout << "\nВвести путь сохранения самостоятельно или воспользоваться сохранением по умолчанию? (0 - по умолчанию, 1 - самостоятельно): ";
			std::string path = "";
			bool sw = (bool)getCorrectValue<int>(true, 0, 1);
			if (sw) {
				std::cout << "\nВведите путь к директории файла(указывать имя файла не нужно, т.к. файл имеет имя базы данных): ";
				std::getline(std::cin, path);
			}
			else {
				char current_work_dir[FILENAME_MAX];
				_getcwd(current_work_dir, sizeof(current_work_dir));
				path = current_work_dir;
			}

			if (!(*this).sData.SaveDataBase(path)) {
				std::cout << "\nОшибка: не верно указан путь к директории файла или базы данных с именем " <<
					"\"" << (*this).sData.GetTableName() << "\"" << " не существует.\n";
				loadScreen();
				break;
			}
			std::cout << "\nДанные базы данных сохранены\n";
			loadScreen();
			break;
		}
		case 5: {
			std::cout << "\nВвести путь загрузки файла самостоятельно или указать путь по умолчанию? (0 - по умолчанию, 1 - самостоятельно): ";
			std::string path = "";
			bool sw = (bool)getCorrectValue<int>(true, 0, 1);
			if (sw) {
				std::cout << "\nВведите полный путь к файлу: ";
				std::getline(std::cin, path);
			}
			else {
				char current_work_dir[FILENAME_MAX];
				_getcwd(current_work_dir, sizeof(current_work_dir));
				path = current_work_dir;
				path += "\\" + (*this).sData.GetTableName() + ".txt";
			}
			if (!(*this).sData.LoadDataBase(path)) {
				std::cout << "\nОшибка: не верно указан путь к файлу или базы данных не существует\n";
				loadScreen();
				break;
			}
			std::cout << "\nДанные загружены\n";
			(*this).sDataColumn = (*this).sData.GetColumn();
			(*this).sData.DataStringTable(&((*this).sDataTable));
			loadScreen();
			break;
		}
		case 6: {
			std::cout << "\tВывод данных на консоль: \n\n";
			std::cout << "Имя базы данных: " << (*this).sData.GetTableName() << "\n\n";
			(*this).OutputData();
			std::cout << std::endl;
			system("PAUSE");
			break;
		}
		}

	}
}
