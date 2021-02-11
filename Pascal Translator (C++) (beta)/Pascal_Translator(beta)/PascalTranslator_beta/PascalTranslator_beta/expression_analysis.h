#pragma once

#include "begin_stack_end.h"

//����� ����������� �������� ���������
//��������� ���������:
//1 �������� ������ ���������� � 1 ������� ������.
//�.�. (1+2), ((1+4)/90), (((1+5)+6)-90) (1 �������� = 2 ������� ������)
//� ������� �� ����� ���� ���������� ���� char, int, double

//������� ���� ����� ������:
//������ ����� ������ �������� �� ���� ����� ����� � ����������� ��� � ����� �������� ������ ����� ����.

class expression_analysis
{
public:
	typedef enum {
		error_not_variable = 0,
		error_syntax = 1,
		error_system = 2,
		error_empty = 3
	}error_expression;
public:
	expression_analysis(begin_stack_end*&);
	~expression_analysis();

private:
	expression_analysis();

	error_expression _error;

	short begin; //������ ���������
	short end;	 //����� ���������
	short counter_exp; //���-�� ���������

	char* _text_exp;//���� ���������
	short size_exp; //����� ���������
	data_stack::type_data _type_exp; //��� ���������

	char* _text_code; //����� ����
	short size_code;  //����� ����

	begin_stack_end* _bse;

public:

	void PutCodeText(char*); //������ ����
	void FindNewExpression(); //���� ����� ���������
	void FindAllExpression(); //����� ���� ��������� � ������, �� ���������� ����� ��������� � counter_exp

	bool ExpressionCheck(); //�������� ��������� �� ������������
	//���� ���������: ����������� ���� ���������
	//� ������� �������.

	bool LowBracketCheck(short, short); //�������� ������ ���� (�+ , +�)
	bool LocalBracketCheck(short, short);//�������� ������ ���� (a+b)
	bool BracketCheck(); //�������� �� ������������ �����

};

