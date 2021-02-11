#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <iostream>

//Описание файла:
//Здесь содержатся функции, для работы со строками.
//Осуществлена реализация:
//копирование, длинномер, сравнение строк, конкатенация строк, дополнение строки.  
//Для оптимизации стеков функций, используется тип short

//в качестве размера строк принят тип - short
//все строки должны оканчиваться нулём-терминатором
//используя данные функции, следует учитывать, что указатель на строку должен
//быть равен(первоначально) NULL.

short StrLen(char*);
bool StrEquallyStr(char*, char*);
void ConcatStr(char*, char*, char*&);
void CopyStr(char*, char*&);
void SaveCopyStr(char*, char*&);


//Добавление функций для перевода строки в число(16.03.2019)

short DegreeValue(short, short);
short One_StringInValue(char);
short StringInValue(char*);

//Добавление функций для определения принадлежности символа к строке(06.06.19)

bool SymbolEquallyStr(char, char*);

//30.07.19

template<typename T>
T TDegreeValue(T a, short b) {
	if (b <= 0)
		return 1;
	else if (b == 1)
		return a;

	T k = a;

	for (char t = 1; t < b; t++)
		a *= k;

	return a;
}