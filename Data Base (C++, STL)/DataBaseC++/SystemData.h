#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>

//����������� ������:
//��������� �������
//��������� ������� � ����
//�������� ���������� ������� ����� ��������� � ������

struct DataColumn {
	std::string type;
	std::string name;
};

class SystemData
{
private:
	const char delimiter = ' '; //��� ��������� ������������ ����� ���������
	const char delimiterString = '\n'; //���������� ����� �����
	const char delimiterType = '-'; //����������� ����� ��������� � ������
	std::string nameTable;
	std::vector<DataColumn> column;
	std::vector<std::vector<std::string> > tableData;

public:
	SystemData();

	bool isTable()const;
	bool CreateTable(const std::string, const std::vector<DataColumn>&); //�������� �������
	std::vector<DataColumn> GetColumn()const;
	size_t GetTableSize()const;
	std::string GetTableName()const;
	bool DataStringTable(std::vector<std::vector<std::string> >*, const size_t = 0, ...); //���������� ������� �������
	bool DataStringTable(std::vector<std::vector<std::string> >*, const std::vector<std::string>*);
	bool DeleteStringTable(const size_t); //�������� ������ �������
	bool SaveDataBase(const std::string = ""); //���������� ���� ������
	bool LoadDataBase(std::string = ""); //�������� ���� ������
	bool SortTable(const std::string, const std::string = "quick");
	unsigned int Find(std::vector<std::vector<std::string> >*, const std::string, const std::string); //�������������� � ���������� ������� � ���. ��������� � ���. �������
	unsigned int Find(std::vector<std::vector<std::string> >*, const size_t, ...); //�������������� � ���-�� ���������� ���. ������ � �������
	unsigned int FindIf(std::vector<std::vector<std::string> >*, bool(*func)(std::vector<std::string>)); //����� �� �������

private:
	//������� ����������
	void Swap(std::vector<std::string>&, std::vector<std::string>&);
	int Partition(std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void QuickSortImpl(std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void QuickSort(std::vector<std::vector<std::string> >&, const size_t&);

	//����������� ����������
	void BubbleSort(std::vector<std::vector<std::string> >&, const size_t&);

	//���������� ��������
	void MergeSortImpl(std::vector<std::vector<std::string> >&, std::vector<std::vector<std::string> >&, int, int, const size_t&);
	void MergeSort(std::vector<std::vector<std::string> >&, const size_t&);

};

