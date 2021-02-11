#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <iostream>

//�������� �����:
//����� ���������� �������, ��� ������ �� ��������.
//������������ ����������:
//�����������, ���������, ��������� �����, ������������ �����, ���������� ������.  
//��� ����������� ������ �������, ������������ ��� short

//� �������� ������� ����� ������ ��� - short
//��� ������ ������ ������������ ����-������������
//��������� ������ �������, ������� ���������, ��� ��������� �� ������ ������
//���� �����(�������������) NULL.

short StrLen(char*);
bool StrEquallyStr(char*, char*);
void ConcatStr(char*, char*, char*&);
void CopyStr(char*, char*&);
void SaveCopyStr(char*, char*&);


//���������� ������� ��� �������� ������ � �����(16.03.2019)

short DegreeValue(short, short);
short One_StringInValue(char);
short StringInValue(char*);

//���������� ������� ��� ����������� �������������� ������� � ������(06.06.19)

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