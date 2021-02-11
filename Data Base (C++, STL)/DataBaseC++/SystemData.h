#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>

//Возможности класса:
//Создавать таблицу
//Сохранять таблицу в файл
//Изменять содержимое таблицы внося изменения в данные

struct DataColumn {
	std::string type;
	std::string name;
};

class SystemData
{
private:
	const char delimiter = ' '; //Чем заполнять пространство между столбцами
	const char delimiterString = '\n'; //Заполнение между строк
	const char delimiterType = '-'; //заполнитель между столбцами и типами
	std::string nameTable;
	std::vector<DataColumn> column;
	std::vector<std::vector<std::string> > tableData;

public:
	SystemData();

	bool isTable()const;
	bool CreateTable(const std::string, const std::vector<DataColumn>&); //Создание таблицы
	std::vector<DataColumn> GetColumn()const;
	size_t GetTableSize()const;
	std::string GetTableName()const;
	bool DataStringTable(std::vector<std::vector<std::string> >*, const size_t = 0, ...); //Добавление колонок таблицы
	bool DataStringTable(std::vector<std::vector<std::string> >*, const std::vector<std::string>*);
	bool DeleteStringTable(const size_t); //Удаление строки таблицы
	bool SaveDataBase(const std::string = ""); //сохранение базы данных
	bool LoadDataBase(std::string = ""); //загрузка базы данных
	bool SortTable(const std::string, const std::string = "quick");
	unsigned int Find(std::vector<std::vector<std::string> >*, const std::string, const std::string); //Информирование о количестве записей с опр. значением в опр. колонке
	unsigned int Find(std::vector<std::vector<std::string> >*, const size_t, ...); //Информирование о кол-ом содержании опр. записи в таблице
	unsigned int FindIf(std::vector<std::vector<std::string> >*, bool(*func)(std::vector<std::string>)); //Поиск по условию

private:
	//быстрая сортировка
	void Swap(std::vector<std::string>&, std::vector<std::string>&);
	int Partition(std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void QuickSortImpl(std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void QuickSort(std::vector<std::vector<std::string> >&, const size_t&);

	//пузырьковая сортировка
	void BubbleSort(std::vector<std::vector<std::string> >&, const size_t&);

	//сортировка слиянием
	void MergeSortImpl(std::vector<std::vector<std::string> >&, std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void MergeSort(std::vector<std::vector<std::string> >&, const size_t&);

};

