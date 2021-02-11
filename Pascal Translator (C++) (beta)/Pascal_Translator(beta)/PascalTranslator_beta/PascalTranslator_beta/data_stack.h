#pragma once

#include <cassert>
#include <typeinfo>
#include "stringw.h"

//iostream исп. для сигнала
#include <iostream>

//ВСЁ ЧТО ТУТ НУЖНО ПОНЯТЬ(ПОВТОРИТЬ):
//Этот класс описывает действия с переменной определённого типа. Смешение типов запрещено.

/*
	Данный класс осуществляет создание переменной одного из доступных типов данных, которые могут быть использованы
	при написании программы на Pascal;
	Типы данных которые будут присутствовать: char, int, double.
	Арифметические операции должны поддерживаться, а именно: +, -, /, *, ^(возведение в степень)


	Переменная - наименьшая единица стека. Стек состоит из переменных. В стеке будет происходить работа с переменными.
	Стек визуально идентифицируется в Pascal коде последовательностью begin и end

	data_stack - класс описывающий функционал одной переменной.
*/

extern bool NameVariableCheck(char*);
extern bool SymbolVariableCheck(char);
extern bool SymbolExpressionCheck(char);
extern bool SymbolValueCheck(char);
extern bool SymbolArifmeticCheck(char);

//Нижеописанный контейнер служит для хранения памяти на определённое время.
//Это специфический метод который необходим для того, чтобы корректно обрабатывать арифметические операции проводимые над переменными (объектами класса data_stack)
template<typename TPoint>
class container_pointer { 
private:
	TPoint** _container;
	short size;
	//С данным контейнером связан недочёт, с освобождением памяти.
	//Этот недочёт, который приводит к тому, что размер программы растёт, на время прийдётся оставить.
	//Это связано с тем, что недочёт не кретический и он тормозит процесс разработки программы.
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
		//причина такого поведения функции непонятна. Нужно разобраться в этой проблеме.
		//Задача: разобраться с проблемой в модели памяти.
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
		empty_type = 3    //тип данных отсутствует
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
	void*		_variable;  //память по которой находится значение определённого типа, для использования в программе
	type_data	_tvar;		//тип памяти (переменной)
	type_error	_error;		//тип ошибки

	//перечень контейренов которые будут использоваться для формирования устойчивой модели памяти относительно выражений
	container_pointer<data_stack> _container_amount; //Основная проблема заключается в том, что одного контейнера нет
	//Т.е. как это понять..изменение контейнера происходит в операторах но ведь операторы не обязательно вызываются из одного объекта.
	//тем самым заставляя нас задуматься о том, что необходимо память удалять по другому. Хотя если объекты временные, то они и сами удалятся.
	container_pointer<data_stack> _container_difference;
	container_pointer<data_stack> _container_multiplication;
	container_pointer<data_stack> _container_division;
	container_pointer<data_stack> _container_exponentiation;

	char* name_variable; //имя переменной

public:

	void delete_variable();

	//переменные любого типа поддерживают арифметические операции такик как: +, -, *, /, ^
	template<typename T>
	void switcher_type(type_data& _tds) {
		//эта функция определяет какую константу нужно присвоить _tds
		//значение которой идентифицирует тип данных data_stack
		//data_stack представляет собой переменную имеющую тип и значение, а также имя.
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
		//Проверка типов на соответствие обязательна! Приведение типов отсутствует.
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
		//операция применяемая к объекту класса data_stack изменяет содержимое data_stack
		//а такой подход неверен - арифметические операции с числами и другими переменными которые будут использовать объекты класса
		//data_stack не должны изменять содержимое этих объектов
		//с этой целью в данном операторе будет создана статическая память, которая позволит устранить эту проблему.
		assert(_error == empty_error); //изолирование ошибок

		type_data _stype = empty_type;
		switcher_type<T>(_stype);

		//существует не уверенность в том, что эта статическая переменная не будет различной по отношению к другим объектам,
		//которые вызовут этот оператор. Т.е. предполагается что для разных объектов которые используют эту операцию
		//статическая переменная _static_stack будет так же различна. Но это только предположение. Если это будет не так, тогда потребуется
		//другой подход.
		//static container_pointer<T> _static_pointer;
		//static data_stack _static_stack;
		//_static_stack = (*this); //в данной строке находится объяснение того, что при применении операции + с объектом и константным значением
		//последующий вызовы этого же оператора будет давать только одно значение.

		//Подход нужно сменить.
		//Здесь особо не развернёшься. Нужно создавать контейнер, который бы содержал и уничтожал последовательно появившуюся память и который\
		//инициировал обращение к этой памяти и её непосредственное удаление в адресном пространстве программы
		//Задача: реализовать данный подход
		
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
		assert(_error == empty_error); //если ошибка есть, то программа вылетает

		type_data _stype = empty_type;
		switcher_type<T>(_stype); //определение типа значения, с которым будет производится арифметическая операция относительно данной переменной

		data_stack _static_stack; //статическая переменная в стеке функции-оператора
		//контейнер вбирает в себя значения и динамически распределяет эти значения по памяти.
		//Т.е. контейнеру идёт значение на вход, он создаёт указатель на это значение и присваивает ему значение. Тем самым в адресном
		//пространстве программы повышается объём хранимой памяти.
		//А затем, эта память используется в арифметических операциях. Этот метод позволяет производить вычисления
		//принимая во внимание частного случая области видимости переменной типа data_stack
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

		_container_difference = _static_stack; //память в адресном пространстве увеличивается, т.к. контейнер добавляет указатель на память
		//в массив указателей на память, в которых хранятся данные для произведения расчёта.

		return _container_difference.GetLastAddressPoint(); //возвращение ссылки на последнюю созданную память.(создаётся при присвоении объекту класса container_pointer значения data_stack)
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
		//возвращает преобразованное значение атрибута класса data_stack
		return *(T*)(_variable);
	}

	void SetNameVariable(char*);
	void GetNameVariable(char*&);
	char* GetPointerNameVariable();
	type_error GetError();
	type_data GetTypeVariable();

	void SetSpecialError();
};

