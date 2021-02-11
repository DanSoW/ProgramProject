#include "Interface.h"

//���. ������� ��� ������

void loadScreen(const unsigned int time, unsigned int count, const char symbol) { //������������� ����� �� ��������� ����� � ������� ���. ������� �� �������
	std::cout << "\t";
	while (count--) {
		std::cout << symbol << " ";
		Sleep(time);
	}
}

//�������� ������ �� n ��������
void CreateTabulateString(std::string& text, size_t n) {
	text.clear();
	for (size_t i = 0; i < n; i++)
		text += " ";
}

int Absolute(int value) {
	return (value > 0) ? value : -value;
}

//�������� �����(���������� ����)

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
			std::cout << "������� ���������� ����� �� ��������� " << "[ " << min << " ; " << max << " ] "
				<< " (���: " << std::string(typeid(T).name()) + " ) : ";
		}
		else {
			std::cout << "������� ���������� ����� (��� " + std::string(typeid(T).name()) + " ): ";
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
			throw std::string("������: �� ������� ��������� ������ �� �����.\n");
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
		std::cout << "������: ���� ������ �����.\n";
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
	std::cout << "������� �������� ���� ������: ";
	std::string name = "";
	std::getline(std::cin, name);

	std::cout << "������� ����� ��������: ";
	size_t n_column = getCorrectValue<size_t>(true, 0, 50);

	std::vector<DataColumn> columns(n_column);

	for (size_t i = 0; i < n_column; i++) {
		/*std::string text = "������� ��� " + std::string(itoa(i, nullptr, 10));
		std::copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout, " "));*/
		std::cout << "������� �������� " << (i + 1) << "-�� �������: ";
		std::getline(std::cin, columns[i].name);
		std::cout << "������� ���(int, double, string) " << (i + 1) << "-�� �������: ";
		std::getline(std::cin, columns[i].type);
		/*if ((columns[i].type != Data::intType)
			&& (columns[i].type != Data::doubleType)
			&& (columns[i].type != Data::stringType)) {
			std::cout << "������: ����� �� ���������� ��� �������. ��� ������ ���� �� 3-� ���������: int, double � string.\n";
			return;
		}*/
	}

	if (!sData.CreateTable(name, columns)) {
		std::cout << "������: ����� �� ���������� ��� �������. ��� ������ ���� �� 3-� ���������: int, double � string.\n";
		return;
	}

	(*this).sData.DataStringTable(&((*this).sDataTable));
	(*this).sDataColumn = (*this).sData.GetColumn();
}

void Interface::InsertData() {
	setlocale(LC_ALL, "rus");
	if (!sData.isTable()) {
		std::cout << "������: ������ ������ ������ � �������������� �������.\n\n";
		return;
	}

	std::vector<std::string> data(sDataColumn.size());
	for (size_t i = 0; i < data.size(); i++) {
		std::cout << "������� ������ � ������� ( " << (i+1) << " ) " << sDataColumn[i].name + ":" + sDataColumn[i].type << " = ";
		std::getline(std::cin, data[i]);
		std::cout << std::endl;
	}

	if (!sData.DataStringTable(nullptr, &data)) {
		std::cout << "������: �������� ������ �� ��������� (������ �����)." << std::endl;
		return;
	}
	
	(*this).sData.DataStringTable(&((*this).sDataTable));
}

void Interface::MenuInterface() {
	setlocale(LC_ALL, "rus");
	while (true) {
		system("cls");
		std::cout << "\t\t����" << std::endl << std::endl;
		std::cout << "1. �������� ���� ������\n";
		std::cout << "2. ���������� ������\n";
		std::cout << "3. �������� ������\n";
		std::cout << "4. ����������\n";
		std::cout << "5. ��������\n";
		std::cout << "6. ����� ���� ������ �� �������\n";
		std::cout << "7. ����� �� ����������������� ����������\n";
		std::cout << "��� �����: ";
		int sw = getCorrectValue<int>(true, 1, 9);
		if (sw == 7)
			break;
		system("cls");

		switch (sw) {
		case 1: {
			(*this).CreateTable();
			std::cout << "\n���� ������ �������\n";
			loadScreen();
			break;
		}
		case 2: {
			bool next = false;
			do {
				system("cls");
				(*this).InsertData();

				std::cout << "���������� ���� ������? (0 - ���, 1 - ��): ";
				next = (bool)getCorrectValue<int>(true, 0, 1);
			} while (next);
			std::cout << "\n���� ������ ��������\n";
			loadScreen();
			break;
		}
		case 3: {
			size_t numberString = 0;
			std::cout << "\n������� ����� ������ ������� ��� �������� (�� 1 �� " << (*this).sData.GetTableSize() << " ) : ";
			numberString = getCorrectValue<size_t>(true, 1, (*this).sData.GetTableSize());
			(*this).sData.DeleteStringTable(numberString - 1);
			std::cout << "\n������ ������� �������\n";
			(*this).sData.DataStringTable(&((*this).sDataTable));
			loadScreen();
			break;
		}
		case 4: {
			std::cout << "\n������ ���� ���������� �������������� ��� ��������������� ����������� �� ���������? (0 - �� ���������, 1 - ��������������): ";
			std::string path = "";
			bool sw = (bool)getCorrectValue<int>(true, 0, 1);
			if (sw) {
				std::cout << "\n������� ���� � ���������� �����(��������� ��� ����� �� �����, �.�. ���� ����� ��� ���� ������): ";
				std::getline(std::cin, path);
			}
			else {
				char current_work_dir[FILENAME_MAX];
				_getcwd(current_work_dir, sizeof(current_work_dir));
				path = current_work_dir;
			}

			if (!(*this).sData.SaveDataBase(path)) {
				std::cout << "\n������: �� ����� ������ ���� � ���������� ����� ��� ���� ������ � ������ " <<
					"\"" << (*this).sData.GetTableName() << "\"" << " �� ����������.\n";
				loadScreen();
				break;
			}
			std::cout << "\n������ ���� ������ ���������\n";
			loadScreen();
			break;
		}
		case 5: {
			std::cout << "\n������ ���� �������� ����� �������������� ��� ������� ���� �� ���������? (0 - �� ���������, 1 - ��������������): ";
			std::string path = "";
			bool sw = (bool)getCorrectValue<int>(true, 0, 1);
			if (sw) {
				std::cout << "\n������� ������ ���� � �����: ";
				std::getline(std::cin, path);
			}
			else {
				char current_work_dir[FILENAME_MAX];
				_getcwd(current_work_dir, sizeof(current_work_dir));
				path = current_work_dir;
				path += "\\" + (*this).sData.GetTableName() + ".txt";
			}
			if (!(*this).sData.LoadDataBase(path)) {
				std::cout << "\n������: �� ����� ������ ���� � ����� ��� ���� ������ �� ����������\n";
				loadScreen();
				break;
			}
			std::cout << "\n������ ���������\n";
			(*this).sDataColumn = (*this).sData.GetColumn();
			(*this).sData.DataStringTable(&((*this).sDataTable));
			loadScreen();
			break;
		}
		case 6: {
			std::cout << "\t����� ������ �� �������: \n\n";
			std::cout << "��� ���� ������: " << (*this).sData.GetTableName() << "\n\n";
			(*this).OutputData();
			std::cout << std::endl;
			system("PAUSE");
			break;
		}
		}

	}
}
