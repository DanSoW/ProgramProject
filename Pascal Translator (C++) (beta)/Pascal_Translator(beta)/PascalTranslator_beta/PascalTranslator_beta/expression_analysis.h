#pragma once

#include "begin_stack_end.h"

//класс анализирует числовое выражение
//Небольшие пояснения:
//1 операция должна заключатся в 1 круглые скобки.
//т.е. (1+2), ((1+4)/90), (((1+5)+6)-90) (1 операция = 2 круглые скобки)
//в скобках не более двух аргументов типа char, int, double

//ГЛАВНАЯ ИДЕЯ ЭТОГО КЛАССА:
//Объект этого класса получает на вход адрес стека и программный код а затем проводит анализ этого кода.

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

	short begin; //начало выражения
	short end;	 //конец выражения
	short counter_exp; //кол-во выражений

	char* _text_exp;//текс выражения
	short size_exp; //длина выражения
	data_stack::type_data _type_exp; //тип выражения

	char* _text_code; //текст кода
	short size_code;  //длина кода

	begin_stack_end* _bse;

public:

	void PutCodeText(char*); //запись кода
	void FindNewExpression(); //ищет новое выражение
	void FindAllExpression(); //поиск всех выражений в тексте, их количество будет находится в counter_exp

	bool ExpressionCheck(); //проверка выражения на корректность
	//чего нехватает: определение типа выражения
	//и многого другого.

	bool LowBracketCheck(short, short); //проверка скобок вида (а+ , +а)
	bool LocalBracketCheck(short, short);//проверка скобок вида (a+b)
	bool BracketCheck(); //проверка на корректность собок

};

