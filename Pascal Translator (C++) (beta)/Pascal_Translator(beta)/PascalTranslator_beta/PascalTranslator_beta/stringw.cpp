#include "stdafx.h"
#include "stringw.h"

short StrLen(char* str) {
	if (str == NULL)
		return 0;
	short k = 0;
	while (*(str++)) k++;
	return k;
}

bool StrEquallyStr(char* str1, char* str2) {
	short k1 = StrLen(str1), k2 = StrLen(str2);
	if ((k1 != k2) || (str1 == NULL) || (str2 == NULL))
		return false;

	for (short i = 0; i < k1; i++)
		if (str1[i] != str2[i])
			return false;

	return true;
}

void ConcatStr(char* str1, char* str2, char*& str) {
	if (str != NULL) {
		delete[] str;
		str = NULL;
	}
	short k1 = StrLen(str1), k2 = StrLen(str2);
	if (k1 && k2) {
		short k = (k1 + k2 + 1);
		str = new char[k];
		ZeroMemory(str, (sizeof(char)*k));
		for (short i = 0; i < k1; i++)
			str[i] = str1[i];
		for (short i = k1, j = 0; (i < (k - 1) && (j < k2));i++, j++)
			str[i] = str2[j];
		return;
	}else if(k1 || k2){
		short r = (k1) ? k1 : k2;
		short k = (r + 1);
		str = new char[k];
		ZeroMemory(str, (sizeof(char)*k));
		if (k1) {
			for (short i = 0; i < r; i++)
				str[i] = str1[i];
			return;
		}

		for (short i = 0; i < r; i++)
			str[i] = str2[i];
		return;
	}
	str = NULL;

	return;
}

void CopyStr(char* str1, char*& str) {
	if (str != NULL) {
		delete[] str;
		str = NULL;
	}
	if (str1 == NULL)
		return;
	short k1 = StrLen(str1);
	str = new char[k1 + 1];
	ZeroMemory(str, (sizeof(char)*(k1 + 1)));
	for (short i = 0; i < k1; i++)
		str[i] = str1[i];

	return;
}

void SaveCopyStr(char* str1, char*& str) {
	if (str1 == NULL)
		return;
	short k1 = StrLen(str1);
	if (str == NULL) {
		CopyStr(str1, str);
		return;
	}
	short k2 = StrLen(str);
	char* str2 = new char[k2+1];
	ZeroMemory(str2, (sizeof(char)*(k2 + 1)));
	for (short i = 0; i < k2; i++)
		str2[i] = str[i];

	delete[] str;
	str = NULL;
	short k = (k1 + k2 + 1);
	str = new char[k];
	ZeroMemory(str, (sizeof(char)*k));

	for (short i = 0; i < k2; i++)
		str[i] = str2[i];
	for (short i = k2, j = 0; ((i < (k - 1)) && (j < k1)); i++, j++)
		str[i] = str1[j];
	
	delete[] str2;
	str2 = NULL;

	return;
}


//16.03.2019

short DegreeValue(short a, short b) {
	if (b <= 0)
		return 1;
	else if (b == 1)
		return a;

	short k = a;

	for (char t = 1; t < b; t++)
		a *= k;

	return a;
}

short One_StringInValue(char ch) {
	if (((short)ch < 48) || ((short)ch > 57))
		return (-1);

	return ((short)ch - 48);
}

short StringInValue(char* str) {
	if (str == NULL)
		return (-1);
	short k = StrLen(str);
	if (k <= 0)
		return (-1);

	for (short i = 0; i < k; i++)
		if (((short)str[i] < 48) || ((short)str[i] > 57))
			return (-1);

	short value = 0;

	for (short i = 0; i < k; i++)
		value += One_StringInValue(str[i])*DegreeValue(10, (k-i-1));

	return value;
}


//06.06.19

bool SymbolEquallyStr(char c, char* str) {
	if (str == NULL)
		return false;
	short k = StrLen(str);
	if (k <= 0)
		return false;

	bool t = false;
	for (short i = 0; ((i < k)&&(!t)); i++)
		if (c == str[i])
			t = true;

	return t;
}