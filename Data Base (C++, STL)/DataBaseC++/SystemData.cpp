#include "SystemData.h"

namespace Data {
	const char* intType = "int";
	const char* doubleType = "double";
	const char* stringType = "string";
}

//Дополнительные функции для работы системы:

//Принадлежит ли символ symbol строке text:
bool SymbolEquallyString(char symbol, const std::string& text) {
	if (text.size() <= 0)
		return false;
	for (const auto& item : text)
		if (symbol == item)
			return true;
	return false;
}

//Какой тип имеет строка text:
bool StringHaveTypeInt(const std::string& text) {
	if (text.size() <= 0)
		return false;
	for (const auto& item : text)
		if (!(SymbolEquallyString(item, std::string("0123456789"))))
			return false;
	return true;
}

bool StringHaveTypeDouble(const std::string& text) {
	if (text.size() <= 0)
		return false;
	for (const auto& item : text)
		if (!(SymbolEquallyString(item, std::string("0123456789."))))
			return false;
	return (text.find('.') == text.rfind('.'));
}

//Преобразование строки в числовое значения типа int(в double исп. atof)
int StringToNumber(std::string value, bool& flagError) {
	flagError = false;
	if (StringHaveTypeInt(value))
		return atoi(value.c_str());
	else if (StringHaveTypeDouble(value)) {
		flagError = true;
		return 0;
	}
	
	int sum = 0;
	std::for_each(value.begin(), value.end(), [&sum](const auto& item) {
		sum += static_cast<int>(item);
		});
	return sum;
}

//Алгоритм split(разделения строки на подстроки)
std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

SystemData::SystemData(){}

bool SystemData::isTable() const {
	return ((*this).column.size() > 0);
}

bool SystemData::CreateTable(const std::string nameT, const std::vector<DataColumn>& dataColumn) {
	(*this).nameTable = "";
	(*this).column.clear();
	(*this).tableData.clear();

	//Запись данных о столбцах
	for (size_t i = 0; i < dataColumn.size(); i++)
		if (std::count_if(dataColumn.begin(), dataColumn.end(), [&dataColumn, &i](const auto& item) -> bool {
			return dataColumn[i].name == item.name;
			}) > 1) {
			return false;
		}

	try {
		std::vector<std::string> types;
		types.push_back(Data::intType);
		types.push_back(Data::doubleType);
		types.push_back(Data::stringType);

		for(const auto & item : dataColumn) {
			bool typeIsActive = false;
			for (const auto& type : types) {
				if (type == item.type) {
					typeIsActive = true;
					break;
				}
			}
			if (!typeIsActive)
				throw (-1);
		}
		(*this).nameTable = nameT;
	}
	catch (int) {
		return false;
	}

	if ((*this).nameTable == "")
		return false;

	std::copy(dataColumn.begin(), dataColumn.end(), std::back_insert_iterator<std::vector<DataColumn> >((*this).column));
	return true;
}

std::vector<DataColumn> SystemData::GetColumn()const {
	return (*this).column;
}

size_t SystemData::GetTableSize()const {
	return tableData.size();
}

std::string SystemData::GetTableName()const {
	return nameTable;
}

bool SystemData::DataStringTable(std::vector<std::vector<std::string> >* pointData, const std::vector<std::string>* data) {
	if ((pointData == nullptr) && ((*data).size() != (*this).column.size()) || ((*this).nameTable.size() <= 0))
		return false;

	if ((pointData != nullptr) && (data == nullptr)) {
		(*pointData) = (*this).tableData;
		return true;
	}

	for (size_t i = 0; i < (*data).size(); i++) {
		if ((((*this).column[i].type == Data::intType) && (!StringHaveTypeInt((*data)[i])))
			|| (((*this).column[i].type == Data::doubleType) && (!StringHaveTypeDouble((*data)[i])))) {
			return false;
		}
	}
	
	(*this).tableData.push_back((*data));

	if (pointData != nullptr)
		(*pointData) = (*this).tableData;

	return true;
}

bool SystemData::DataStringTable(std::vector<std::vector<std::string> >* pointData, const size_t count, ...) {
	//Добавление данных в строку или считывание всех данных
	if (((pointData == nullptr) && (count != (*this).column.size())) || ((*this).nameTable.size() <= 0))
		return false;

	if ((pointData != nullptr) && (!count)) {
		(*pointData) = (*this).tableData;
		return true;
	}

	va_list list;
	std::vector<std::string> data;

	__crt_va_start(list, count);
	for (size_t i = 0; i < count; i++) {
		try {
			data.push_back(__crt_va_arg(list, std::string));
		}
		catch (...) {
			return false;
		}

		if ((((*this).column[i].type == Data::intType) && (!StringHaveTypeInt(data[i])))
			|| (((*this).column[i].type == Data::doubleType) && (!StringHaveTypeDouble(data[i])))) {
			return false;
		}
	}

	if (data.size() == count)
		(*this).tableData.push_back(data);
	
	if(pointData != nullptr)
		(*pointData) = (*this).tableData;

	__crt_va_end(list);
	return true;
}

bool SystemData::DeleteStringTable(const size_t numberColumn) {
	if (numberColumn >= (*this).tableData.size())
		return false;
	(*this).tableData.erase((*this).tableData.begin() + numberColumn);
	return true;
}

bool SystemData::SaveDataBase(const std::string path) {
	if (((*this).nameTable.size() == 0) || ((*this).tableData.size() == 0) || (path.size() == 0)) {
		return false;
	}

	std::ofstream out;
	out.open(path + "\\" + (*this).nameTable + ".txt");
	if (!out.is_open()) {
		return false;
	}
	for (size_t i = 0; i < (*this).column.size(); i++) {
		if (i < ((*this).column.size() - 1))
			out << (*this).column[i].name << (*this).delimiterType
			<< (*this).column[i].type << (*this).delimiter;
		else
			out << (*this).column[i].name << (*this).delimiterType
			<< (*this).column[i].type;
	}
	out << (*this).delimiterString;

	for (size_t i = 0; i < (*this).tableData.size(); i++) {
		for (size_t j = 0; j < (*this).tableData[i].size(); j++) {
			if (j < ((*this).tableData[i].size() - 1))
				out << (*this).tableData[i][j] << (*this).delimiter;
			else
				out << (*this).tableData[i][j];
		}
		out << (*this).delimiterString;
	}
	out.close();

	return true;
}

//Загрузка базы данных из файла(данные файла читаются и после преобразования удобным для программного
//представления сохраняются в this->column и this->tableData)
bool SystemData::LoadDataBase(std::string pathDB) {
	if (pathDB.size() == 0)
		return false;
	if (pathDB == "")
		pathDB = (*this).nameTable;

	(*this).column.clear();
	(*this).tableData.clear();

	if (pathDB.find(".txt") == std::string::npos)
		pathDB += ".txt";
	std::ifstream in;
	in.open(pathDB);
	if (!in.is_open()) {
		return false;
	}

	std::stringstream fullText;
	fullText << in.rdbuf();
	in.close();

	std::string text;
	text = fullText.str();

	std::vector<std::string> strText = split(text, (*this).delimiterString);

	std::vector<std::string> data = split(strText[0], (*this).delimiter);
	for (const auto& item : data) {
		std::vector<std::string> attrData = split(item, (*this).delimiterType);

		if ((attrData.size() != 2) || ((attrData[1] != Data::doubleType) && (attrData[1] != Data::intType)
			&& (attrData[1] != Data::stringType))) {
			(*this).column.clear();
			return false;
		}
		DataColumn dcm;
		dcm.name = attrData[0];
		dcm.type = attrData[1];
		(*this).column.push_back(dcm);
	}
	data.clear();

	//изменения: 14.09.20(проверка на  повторяющиеся колонки)
	for (size_t i = 0; i < (*this).column.size(); i++)
		if (std::count_if((*this).column.begin(), (*this).column.end(), [=, &i](const auto& item) -> bool {
			return column[i].name == item.name;
			}) > 1) {
			(*this).column.clear();
			return false;
		}

	
	for (size_t i = 1; i < strText.size(); i++) {
		std::vector<std::string> textSplit = split(strText[i], (*this).delimiter);
		if ((textSplit.size() != (*this).column.size())) {
			(*this).tableData.clear();
			(*this).column.clear();
			return false;
		}
		(*this).tableData.push_back(textSplit);
		for (size_t j = 0; j < (*this).tableData[(i-1)].size(); j++) {
			if ((((*this).column[j].type == Data::intType) && (!StringHaveTypeInt((*this).tableData[(i - 1)][j])))
				|| (((*this).column[j].type == Data::doubleType) && (!StringHaveTypeDouble((*this).tableData[(i - 1)][j])))) {
				(*this).tableData.clear();
				(*this).column.clear();
				return false;	
			}
		}
	}

	(*this).nameTable = "";
	for (size_t i = (pathDB.rfind("\\") + 1); i < pathDB.find(".txt"); i++)
		(*this).nameTable += pathDB[i];

	return true;
}

//Интерфейс сортировки данных в таблице(сортируются строки между собой по определённым 3-м алгоритмам сортировок:
//1) Быстрая сортировка(по умолчанию)
//2) Пузырьковая сортировка(классика)
//3) Сортировка слиянием
bool SystemData::SortTable(const std::string nameColumn, const std::string nameSort) {
	/*bool t = false; - Одно из решений. Оставлено из-за красоты лямбд выражений

	std::for_each((*this).column.begin(), (*this).column.end(), [&nameColumn, &t](const DataColumn& item) {
		if (nameColumn == item.name)
			t = true;
		});
	if (!t) {
		std::cout << "Error: column with name \'" << nameColumn << "\' is not defined" << std::endl;
		return false;
	}*/

	size_t index = (*this).column.size();
	for (size_t i = 0; i < (*this).column.size(); i++)
		if (nameColumn == (*this).column[i].name) {
			index = i;
			break;
		}

	if (index == (*this).column.size()) {
		return true;
	}

	if(nameSort == "quick")
		QuickSort((*this).tableData, index);
	else if(nameSort == "merge")
		MergeSort((*this).tableData, index);
	else if(nameSort == "bubble")
		BubbleSort((*this).tableData, index);
	else {
		return false;
	}

	return true;
}

//Обмен местами строк таблицы
void SystemData::Swap(std::vector<std::string>& value_a, std::vector<std::string>& value_b) {
	std::vector<std::string> value_c = value_a;
	value_a = value_b;
	value_b = value_c;
}

int SystemData::Partition(std::vector<std::vector<std::string> >& values, int left, int right, const size_t& index) {

	int less = left;
	if (StringHaveTypeDouble(values[0][index])) {
		double x = atof(values[right][index].c_str());
		for(size_t i = left; i < right; i++)
			if (atof(values[i][index].c_str()) <= x) {
				Swap(values[i], values[less]);
				less++;
			}
		Swap(values[less], values[right]);
	}
	else {
		bool flag = false;
		double x = StringToNumber(values[right][index], flag);
		if (flag) {
			return 0;
		}
		for (size_t i = left; i < right; i++)
			if (StringToNumber(values[i][index], flag) <= x) {
				Swap(values[i], values[less]);
				less++;
			}
		Swap(values[less], values[right]);
	}

	return less;
}

void SystemData::QuickSortImpl(std::vector<std::vector<std::string> >& values, int left, int right, const size_t& index) {
	if (left >= right)
		return;
	int q = Partition(values, left, right, index);
	QuickSortImpl(values, left, (q - 1), index);
	QuickSortImpl(values, (q + 1), right, index);
}

void SystemData::QuickSort(std::vector<std::vector<std::string> >& values, const size_t& index) {
	if (values.empty())
		return;

	QuickSortImpl(values, 0, values.size() - 1, index);
}

void SystemData::BubbleSort(std::vector<std::vector<std::string> >& values, const size_t& index) {
	if (values.empty())
		return;

	bool t = true;
	if (StringHaveTypeDouble(values[0][index])) {
		while (t) {
			t = false;
			for (size_t i = 0; i < (values.size() - 1); i++)
				if (atof(values[i][index].c_str()) < atof(values[i + 1][index].c_str())) {
					Swap(values[i], values[i + 1]);
					t = true;
				}
		}
	}
	else {
		while (t) {
			t = false;
			for (size_t i = 0; i < (values.size() - 1); i++)
				if (StringToNumber(values[i][index], t) < StringToNumber(values[i+1][index], t)) {
					Swap(values[i], values[i + 1]);
					t = true;
				}
		}
	}
}

void SystemData::MergeSortImpl(std::vector<std::vector<std::string> >& values, std::vector<std::vector<std::string> >& buf, int left, int right, const size_t& index) {
	if (left >= right)
		return;
	int m = (left + right) / 2;
	MergeSortImpl(values, buf, left, m, index);
	MergeSortImpl(values, buf, (m+1), right, index);

	int k = left;
	if (StringHaveTypeDouble(values[0][index])) {
		for (int i = left, j = (m + 1); (i <= m) || (j <= right);) {
			if ((j > right) || ((i <= m) && (atof(values[i][index].c_str()) < atof(values[j][index].c_str())))) {
				buf[k] = values[i];
				i++;
			}
			else {
				buf[k] = values[j];
				j++;
			}
			k++;
		}
	}
	else {
		bool flag = false;
		for (int i = left, j = (m + 1); (i <= m) || (j <= right);) {
			if ((j > right) || ((i <= m) && (StringToNumber(values[i][index], flag) < StringToNumber(values[j][index], flag)))) {
				buf[k] = values[i];
				i++;
			}
			else {
				buf[k] = values[j];
				j++;
			}
			k++;
		}
	}
	for (int i = left; i <= right; i++)
		values[i] = buf[i];
}

void SystemData::MergeSort(std::vector<std::vector<std::string> >& values, const size_t& index) {
	if (values.empty())
		return;

	std::vector<std::vector<std::string> > buf(values.size());
	MergeSortImpl(values, buf, 0, (values.size() - 1), index);
}

unsigned int SystemData::Find(std::vector<std::vector<std::string> >* pointData, const std::string nameColumn, const std::string value) {
	if ((nameColumn.size() <= 0) || (value.size() <= 0))
		return 0;
	size_t index = (*this).column.size();
	for (size_t i = 0; i < (*this).column.size(); i++)
		if (nameColumn == (*this).column[i].name) {
			index = i;
			break;
		}

	if (index == (*this).column.size()) {
		return true;
	}

	unsigned int count = 0;
	if (pointData != nullptr) {
		std::vector<std::vector<std::string> > copyData;
		for (const auto& item : (*this).tableData)
			if (item[index] == value) {
				copyData.push_back(item);
				count++;
			}

		(*pointData).clear();
		std::copy(copyData.begin(), copyData.end(), std::back_insert_iterator<std::vector<std::vector<std::string>> >((*pointData)));
	}
	else {
		for (const auto& item : (*this).tableData)
			if (item[index] == value)
				count++;
	}

	return count;
}

unsigned int SystemData::Find(std::vector<std::vector<std::string> >* pointData, const size_t count, ...) {
	if ((*this).column.size() != count)
		return 0;

	va_list list;
	__crt_va_start(list, count);

	std::vector<std::string> columnData;

	for (size_t i = 0; i < count; i++) {
		try {
			columnData.push_back(__crt_va_arg(list, std::string));
		}
		catch (...) {
			return 0;
		}
		if ((((*this).column[i].type == Data::intType) && (!StringHaveTypeInt(columnData[i])))
			|| (((*this).column[i].type == Data::doubleType) && (!StringHaveTypeDouble(columnData[i])))) {
			return 0;
		}
	}

	__crt_va_end(list);

	unsigned int countR = 0;
	if (pointData != nullptr) {
		std::vector<std::vector<std::string> > copyData;
		for (const auto& item : (*this).tableData) {
			if (item == columnData) {
				copyData.push_back(item);
				countR++;
			}
		}
		(*pointData).clear();
		std::copy(copyData.begin(), copyData.end(), std::back_insert_iterator<std::vector<std::vector<std::string>> >((*pointData)));
	}
	else {
		for (const auto& item : (*this).tableData) {
			if (item == columnData)
				countR++;
		}
	}

	return countR;
}

unsigned int SystemData::FindIf(std::vector<std::vector<std::string> >* pointData, bool(*func)(std::vector<std::string>)) {
	unsigned int count = 0;

	if (pointData != nullptr) {
		std::vector<std::vector<std::string> > copyData;
		for(const auto& item : (*this).tableData)
			if (func(item)) {
				copyData.push_back(item);
				count++;
			}
		
		(*pointData).clear();
		std::copy(copyData.begin(), copyData.end(), std::back_insert_iterator<std::vector<std::vector<std::string>> >((*pointData)));
	}
	else {
		for (const auto& item : (*this).tableData)
			if (func(item))
				count++;
	}

	return count;
}
