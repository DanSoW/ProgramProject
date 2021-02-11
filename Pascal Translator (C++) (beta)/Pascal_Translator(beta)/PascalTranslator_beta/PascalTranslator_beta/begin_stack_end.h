#pragma once

#include "data_stack.h"

//������� ����� ������� ������:
//������ ����� ��������� ������ ������. ������� � ������� �� ������ ����� ����������. � ����� ������������ �� ����� � ������������ ��������� ����������
//��������� ��������.

class begin_stack_end
{
public:

	typedef enum {
		error_name_var = 0,
		error_empty = 1
	}type_error_stack;
public:
	begin_stack_end();
	~begin_stack_end();

private:
	data_stack * _vstack;
	short size_stack;

	type_error_stack _error;

public:
	void PutVariable(char*, data_stack::type_data); //������������� ���������� ����� �������� 0 (��� ������� � ������������ ���� ����������)

	bool FindVariable(char*);
	bool FindVariable(char*, short&);

	data_stack& GetVariable(char*);

};

