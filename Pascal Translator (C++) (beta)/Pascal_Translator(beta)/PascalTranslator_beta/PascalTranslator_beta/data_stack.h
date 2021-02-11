#pragma once

#include <cassert>
#include <typeinfo>
#include "stringw.h"

//iostream ���. ��� �������
#include <iostream>

//�Ѩ ��� ��� ����� ������(���������):
//���� ����� ��������� �������� � ���������� ������������ ����. �������� ����� ���������.

/*
	������ ����� ������������ �������� ���������� ������ �� ��������� ����� ������, ������� ����� ���� ������������
	��� ��������� ��������� �� Pascal;
	���� ������ ������� ����� ��������������: char, int, double.
	�������������� �������� ������ ��������������, � ������: +, -, /, *, ^(���������� � �������)


	���������� - ���������� ������� �����. ���� ������� �� ����������. � ����� ����� ����������� ������ � �����������.
	���� ��������� ���������������� � Pascal ���� ������������������� begin � end

	data_stack - ����� ����������� ���������� ����� ����������.
*/

extern bool NameVariableCheck(char*);
extern bool SymbolVariableCheck(char);
extern bool SymbolExpressionCheck(char);
extern bool SymbolValueCheck(char);
extern bool SymbolArifmeticCheck(char);

//������������� ��������� ������ ��� �������� ������ �� ����������� �����.
//��� ������������� ����� ������� ��������� ��� ����, ����� ��������� ������������ �������������� �������� ���������� ��� ����������� (��������� ������ data_stack)
template<typename TPoint>
class container_pointer { 
private:
	TPoint** _container;
	short size;
	//� ������ ����������� ������ �������, � ������������� ������.
	//���� �������, ������� �������� � ����, ��� ������ ��������� �����, �� ����� �������� ��������.
	//��� ������� � ���, ��� ������� �� ����������� � �� �������� ������� ���������� ���������.
public:
	container_pointer() {
		_container = NULL;
		size = 0;
		return;
	}
	~container_pointer() {
		(*this).DeleteMemoryContainer();

		return;
	}

	void operator= (TPoint& value) {
		//������� ������ ��������� ������� ���������. ����� ����������� � ���� ��������.
		//������: ����������� � ��������� � ������ ������.
		(*this).DeleteNullEmelent();

		if (_container == NULL) {
			size = 1;
			_container = new TPoint*[size];
			_container[0] = new TPoint;
			*(_container[0]) = value;

			return;
		}

		TPoint** _cont_copy = new TPoint*[size + 1];
		for (short i = 0; i < size; i++)
			_cont_copy[i] = _container[i];

		_cont_copy[size] = new TPoint;
		*(_cont_copy[size]) = value;

		for (short i = 0; i < size; i++)
			_container[i] = NULL;
		delete[] _container;
		_container = NULL;

		_container = _cont_copy;
		size++;

		return;
	}

	void DeleteNullEmelent() {
		if ((_container == NULL) || (size <= 0))
			return;

		short k = 0;
		for (short i = 0; i < size; i++)
			if (_container[i] == NULL)
				k++;
		if (!k)
			return;

		TPoint** _cont_copy = new TPoint*[(size - k)];
		for (short i = 0, j = 0; ((i < size) && (j < (size - k))); i++)
			if (_container[i] != NULL)
				_cont_copy[j++] = _container[i];

		for (short i = 0; i < size; i++)
			_container[i] = NULL;
		delete[] _container;
		_container = NULL;

		_container = _cont_copy;
		size -= k;

		return;
	}

	TPoint& GetAddressPoint(short index) {
		static TPoint _static_null;
		if ((_container == NULL) || (index < 0) || (index >= size))
			return _static_null;

		return (*_container[index]);
	}

	TPoint& GetLastAddressPoint() {
		static TPoint _static_null;
		if ((_container == NULL) || (size <= 0))
			return _static_null;

		return (*_container[(size - 1)]);
	}

	void DeleteMemoryContainer() {
		if (_container == NULL)
			return;
		if (size <= 0)
			assert(false);
		for (short i = 0; i < size; i++)
			if (_container[i] != NULL) {
				delete _container[i];
				_container[i] = NULL;
			}
		delete[] _container;
		_container = NULL;

		size = 0;

		return;
	}


};

class data_stack
{
public:

	typedef enum {
		chard = 0,	 //char
		intd = 1,	 //int
		doubled = 2, //double
		empty_type = 3    //��� ������ �����������
	}type_data;

	typedef enum {
		error_equality = 0,
		error_arifmetic = 1,
		error_memory = 2,
		error_redefination = 3,
		error_name_variable = 4,
		error_special = 5,
		empty_error = 6
	}type_error;
public:

	data_stack();
	~data_stack();

private:
	void*		_variable;  //������ �� ������� ��������� �������� ������������ ����, ��� ������������� � ���������
	type_data	_tvar;		//��� ������ (����������)
	type_error	_error;		//��� ������

	//�������� ����������� ������� ����� �������������� ��� ������������ ���������� ������ ������ ������������ ���������
	container_pointer<data_stack> _container_amount; //�������� �������� ����������� � ���, ��� ������ ���������� ���
	//�.�. ��� ��� ������..��������� ���������� ���������� � ���������� �� ���� ��������� �� ����������� ���������� �� ������ �������.
	//��� ����� ��������� ��� ���������� � ���, ��� ���������� ������ ������� �� �������. ���� ���� ������� ���������, �� ��� � ���� ��������.
	container_pointer<data_stack> _container_difference;
	container_pointer<data_stack> _container_multiplication;
	container_pointer<data_stack> _container_division;
	container_pointer<data_stack> _container_exponentiation;

	char* name_variable; //��� ����������

public:

	void delete_variable();

	//���������� ������ ���� ������������ �������������� �������� ����� ���: +, -, *, /, ^
	template<typename T>
	void switcher_type(type_data& _tds) {
		//��� ������� ���������� ����� ��������� ����� ��������� _tds
		//�������� ������� �������������� ��� ������ data_stack
		//data_stack ������������ ����� ���������� ������� ��� � ��������, � ����� ���.
		if ((StrEquallyStr(const_cast<char*>("char"), const_cast<char*>(typeid(T).name()))) || (StrEquallyStr(const_cast<char*>("c"), const_cast<char*>(typeid(T).name()))))
			_tds = chard;
		else if ((StrEquallyStr(const_cast<char*>("int"), const_cast<char*>(typeid(T).name()))) || (StrEquallyStr(const_cast<char*>("i"), const_cast<char*>(typeid(T).name()))))
			_tds = intd;
		else if ((StrEquallyStr(const_cast<char*>("double"), const_cast<char*>(typeid(T).name()))) || (StrEquallyStr(const_cast<char*>("d"), const_cast<char*>(typeid(T).name()))))
			_tds = doubled;
		else
			_tds = empty_type;

		return;
	}

	template<typename T>
	void operator= (const T value) {
		assert(_error == empty_error);

		type_data _stype = empty_type;
		(*this).switcher_type<T>(_stype);
		//�������� ����� �� ������������ �����������! ���������� ����� �����������.
		if ((_stype == empty_type) || ((_tvar != empty_type) && (_tvar != _stype))) {
			_error = error_equality;
			return;
		}

		if (_variable != NULL)
			(*this).delete_variable();

		if (_tvar == empty_type)
			_tvar = _stype;

		_variable = static_cast<void*>(new T(value));

		return;
	}

	void operator= (data_stack&);
	void operator= (data_stack*);

	template<typename T>
	data_stack& operator+ (const T value) {
		//�������� ����������� � ������� ������ data_stack �������� ���������� data_stack
		//� ����� ������ ������� - �������������� �������� � ������� � ������� ����������� ������� ����� ������������ ������� ������
		//data_stack �� ������ �������� ���������� ���� ��������
		//� ���� ����� � ������ ��������� ����� ������� ����������� ������, ������� �������� ��������� ��� ��������.
		assert(_error == empty_error); //������������ ������

		type_data _stype = empty_type;
		switcher_type<T>(_stype);

		//���������� �� ����������� � ���, ��� ��� ����������� ���������� �� ����� ��������� �� ��������� � ������ ��������,
		//������� ������� ���� ��������. �.�. �������������� ��� ��� ������ �������� ������� ���������� ��� ��������
		//����������� ���������� _static_stack ����� ��� �� ��������. �� ��� ������ �������������. ���� ��� ����� �� ���, ����� �����������
		//������ ������.
		//static container_pointer<T> _static_pointer;
		//static data_stack _static_stack;
		//_static_stack = (*this); //� ������ ������ ��������� ���������� ����, ��� ��� ���������� �������� + � �������� � ����������� ���������
		//����������� ������ ����� �� ��������� ����� ������ ������ ���� ��������.

		//������ ����� �������.
		//����� ����� �� �����������. ����� ��������� ���������, ������� �� �������� � ��������� ��������������� ����������� ������ � �������\
		//����������� ��������� � ���� ������ � � ���������������� �������� � �������� ������������ ���������
		//������: ����������� ������ ������
		
		data_stack _static_stack;

		if ((_stype == empty_type) || ((_tvar != empty_type) && (_tvar != _stype)) || (_variable == NULL)) {
			_error = error_arifmetic;
			return _container_amount.GetLastAddressPoint();
		}

		_static_stack = (*this);

		if (_stype == chard)
			*(char*)(_static_stack._variable) += value;
		else if (_stype == intd)
			*(int*)(_static_stack._variable) += value;
		else if (_stype == doubled)
			*(double*)(_static_stack._variable) += value;

		_container_amount = _static_stack;

		return _container_amount.GetLastAddressPoint();
	}
	data_stack& operator+ (data_stack&);

	template<typename T>
	data_stack& operator- (const T value) {
		assert(_error == empty_error); //���� ������ ����, �� ��������� ��������

		type_data _stype = empty_type;
		switcher_type<T>(_stype); //����������� ���� ��������, � ������� ����� ������������ �������������� �������� ������������ ������ ����������

		data_stack _static_stack; //����������� ���������� � ����� �������-���������
		//��������� ������� � ���� �������� � ����������� ������������ ��� �������� �� ������.
		//�.�. ���������� ��� �������� �� ����, �� ������ ��������� �� ��� �������� � ����������� ��� ��������. ��� ����� � ��������
		//������������ ��������� ���������� ����� �������� ������.
		//� �����, ��� ������ ������������ � �������������� ���������. ���� ����� ��������� ����������� ����������
		//�������� �� �������� �������� ������ ������� ��������� ���������� ���� data_stack
		if ((_stype == empty_type) || ((_tvar != empty_type) && (_tvar != _stype)) || (_variable == NULL)) {
			_error = error_arifmetic;
			return _container_difference.GetLastAddressPoint(); 
		}

		_static_stack = (*this); 

		if (_stype == chard)
			*(char*)(_static_stack._variable) -= value;
		else if (_stype == intd)
			*(int*)(_static_stack._variable) -= value;
		else if (_stype == doubled)
			*(double*)(_static_stack._variable) -= value;

		_container_difference = _static_stack; //������ � �������� ������������ �������������, �.�. ��������� ��������� ��������� �� ������
		//� ������ ���������� �� ������, � ������� �������� ������ ��� ������������ �������.

		return _container_difference.GetLastAddressPoint(); //����������� ������ �� ��������� ��������� ������.(�������� ��� ���������� ������� ������ container_pointer �������� data_stack)
	}
	data_stack& operator- (data_stack&);

	template<typename T>
	data_stack& operator* (const T value) {
		assert(_error == empty_error);

		type_data _stype = empty_type;
		switcher_type<T>(_stype);

		data_stack _static_stack;

		if ((_stype == empty_type) || ((_tvar != empty_type) && (_tvar != _stype)) || (_variable == NULL)) {
			_error = error_arifmetic;
			return _container_multiplication.GetLastAddressPoint();
		}

		_static_stack = (*this);

		if (_stype == chard)
			*(char*)(_static_stack._variable) *= value;
		else if (_stype == intd)
			*(int*)(_static_stack._variable) *= value;
		else if (_stype == doubled)
			*(double*)(_static_stack._variable) *= value;

		_container_multiplication = _static_stack;

		return _container_multiplication.GetLastAddressPoint();
	}
	data_stack& operator* (data_stack&);

	template<typename T>
	data_stack& operator/ (const T value) {
		assert(_error == empty_error);

		type_data _stype = empty_type;
		switcher_type<T>(_stype);

		data_stack _static_stack;

		if ((_stype == empty_type) || ((_tvar != empty_type) && (_tvar != _stype)) || (_variable == NULL) || (!value)) {
			_error = error_arifmetic;
			return _container_division.GetLastAddressPoint();
		}

		_static_stack = (*this);

		if (_stype == chard)
			*(char*)(_static_stack._variable) /= value;
		else if (_stype == intd)
			*(int*)(_static_stack._variable) /= value;
		else if (_stype == doubled)
			*(double*)(_static_stack._variable) /= value;

		_container_division = _static_stack;

		return _container_division.GetLastAddressPoint();
	}
	data_stack& operator/ (data_stack&);

	data_stack& operator^ (const short);

	template<typename T>
	T get_value() {
		//���������� ��������������� �������� �������� ������ data_stack
		return *(T*)(_variable);
	}

	void SetNameVariable(char*);
	void GetNameVariable(char*&);
	char* GetPointerNameVariable();
	type_error GetError();
	type_data GetTypeVariable();

	void SetSpecialError();
};

