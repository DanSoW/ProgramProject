#pragma once

#include <Windows.h>
#include "SystemData.h"
#include <iterator>
#include <direct.h>
#include <cstdlib>

#undef max

void loadScreen(const unsigned int = 200, unsigned int = 10, const char = '*');

class Interface
{
private:
	SystemData sData;
	std::vector<DataColumn> sDataColumn;
	std::vector<std::vector<std::string> > sDataTable;

public:
	Interface();
	Interface(std::string);

	void OutputData(std::string = "      ", const bool = false) const;
	void CreateTable();
	void InsertData();
	void MenuInterface();
};

