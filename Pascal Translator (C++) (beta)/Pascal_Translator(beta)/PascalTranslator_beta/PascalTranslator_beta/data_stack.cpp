#include "stdafx.h"
#include "data_stack.h"

bool NameVariableCheck(char* name) {
	short k = StrLen(name);
	bool t = true;

	for (short i = 0; (i < k) && (t); i++)
		if (((int)name[i] < 65) || (((int)name[i] > 90) && ((int)name[i] < 97)) || ((int)name[i] > 122))
			t = false;

	return t;
}

bool SymbolVariableCheck(char symbol) {
	return ((((int)symbol >= 65) && ((int)symbol <= 90)) || (((int)symbol >= 97) && ((int)symbol <= 122)));
}

bool SymbolExpressionCheck(char symbol) {
	return (SymbolVariableCheck(symbol) || SymbolEquallyStr(symbol, const_cast<char*>("=:;().+-*/^")) || (((int)symbol >= 48) && ((int)symbol <= 57)));
}

bool SymbolValueCheck(char symbol) {
	return (((int)symbol >= 48) && ((int)symbol <= 57));
}

bool SymbolArifmeticCheck(char symbol) {
	return SymbolEquallyStr(symbol, const_cast<char*>("+-*/^"));
}

data_stack::data_stack(){
	_variable = NULL;
	_tvar = empty_type;
	_error = empty_error;
	name_variable = NULL;

	return;
}


data_stack::~data_stack(){
	(*this).delete_variable();
	if (name_variable != NULL) {
		delete[] name_variable;
		name_variable = NULL;
	}

	return;
}

void data_stack::delete_variable() {
	if (_variable != NULL) {
		switch (_tvar) {
		case chard: {
			delete (char*)(_variable);
			break;
		}
		case intd: {
			delete (int*)(_variable);
			break;
		}
		case doubled: {
			delete (double*)(_variable);
			break;
		}

		case empty_type:
		default: {
			delete (_variable); //в процессе работы программы на этой строке вызывается исключение
			//возможно это связано с неправильной работой модели памяти которая здесь присутствует.
			assert(false);
			return;
		}
		}

		_variable = NULL;
	}

	_tvar = empty_type;

	return;
}

void data_stack::operator= (data_stack& value) {
	assert(_error == empty_error);

	if (value._variable == NULL) {
		(*this)._error = error_equality;
		return;
	}

	if ((value._error != empty_error) || ((_tvar != empty_type) && (_tvar != value._tvar)) || (value._tvar == empty_type)) {
		(*this)._error = error_equality;
		return;
	}

	if (_variable != NULL) {
		if (_tvar == empty_type) {
			_error = error_equality;
			delete _variable; //удаляем память, не смотря на то, что не знаем её тип. Это сделано для того, чтобы уменьшить памяти которая сложилась в результате утечки
			//т.е. там есть память..но её тип стал неизвестен...в данном случае при удалении уместно доверится компилятору, даже если тип памяти
			//был вещественным, а компилятор удалит содержимое памяти как целочисленное (т.е. укоротит объём удаляемой памяти), то при этом
			//память которая не удалится всеравно станет меньше, а если бы мы её вообще не удаляли, была бы "полная" утечка памяти.
			_variable = NULL;
			return;
		}
		if (_tvar == chard)
			*((char*)(_variable)) = *(char*)(value._variable);
		else if(_tvar == intd)
			*((int*)(_variable)) = *(int*)(value._variable);
		else if(_tvar == doubled)
			*((double*)(_variable)) = *(double*)(value._variable);

		return;
	}

	_tvar = value._tvar;

	if (_tvar == chard)
		_variable = static_cast<void*>(new char(*(char*)(value._variable)));
	else if (_tvar == intd)
		_variable = static_cast<void*>(new int(*(int*)(value._variable)));
	else if (_tvar == doubled)
		_variable = static_cast<void*>(new double(*(double*)(value._variable)));

	if (_variable == NULL) {
		_error = error_memory;
		return;
	}

	//далее...идёт подстраховка модели памяти принятой за основу..но имеющая недочёт..(не исправленный, но не кретический)
	_container_amount.DeleteMemoryContainer();
	_container_difference.DeleteMemoryContainer();
	_container_multiplication.DeleteMemoryContainer();
	_container_division.DeleteMemoryContainer();
	_container_exponentiation.DeleteMemoryContainer();

	return;
}

void data_stack::operator= (data_stack* value) {
	assert(_error == empty_error);

	if (value == NULL) {
		(*this)._error = error_memory;
		return;
	}

	if ((*value)._variable == NULL) {
		(*this)._error = error_equality;
		return;
	}

	if (((*value)._error != empty_error) || ((_tvar != empty_type) && (_tvar != (*value)._tvar)) || ((*value)._tvar == empty_type)) {
		(*this)._error = error_equality;
		return;
	}

	if (_variable != NULL) {
		if (_tvar == empty_type) {
			_error = error_equality;
			delete _variable; //удаляем память, не смотря на то, что не знаем её тип. Это сделано для того, чтобы уменьшить памяти которая сложилась в результате утечки
							  //т.е. там есть память..но её тип стал неизвестен...в данном случае при удалении уместно доверится компилятору, даже если тип памяти
							  //был вещественным, а компилятор удалит содержимое памяти как целочисленное (т.е. укоротит объём удаляемой памяти), то при этом
							  //память которая не удалится всеравно станет меньше, а если бы мы её вообще не удаляли, была бы "полная" утечка памяти.
			_variable = NULL;
			return;
		}
		if (_tvar == chard)
			*((char*)(_variable)) = *(char*)((*value)._variable);
		else if (_tvar == intd)
			*((int*)(_variable)) = *(int*)((*value)._variable);
		else if (_tvar == doubled)
			*((double*)(_variable)) = *(double*)((*value)._variable);

		return;
	}

	_tvar = (*value)._tvar;

	if (_tvar == chard)
		_variable = static_cast<void*>(new char(*(char*)((*value)._variable)));
	else if (_tvar == intd)
		_variable = static_cast<void*>(new int(*(int*)((*value)._variable)));
	else if (_tvar == doubled)
		_variable = static_cast<void*>(new double(*(double*)((*value)._variable)));

	if (_variable == NULL) {
		_error = error_memory;
		return;
	}

	_container_amount.DeleteMemoryContainer();
	_container_difference.DeleteMemoryContainer();
	_container_multiplication.DeleteMemoryContainer();
	_container_division.DeleteMemoryContainer();
	_container_exponentiation.DeleteMemoryContainer();

	return;
}

data_stack& data_stack::operator+ (data_stack& value) {
	assert(_error == empty_error);

	data_stack _static_stack;

	if ((_variable == NULL) || ((_tvar != empty_type) && (_tvar != value._tvar)) || (value._variable == NULL) || (value._tvar == empty_type)) {
		_error = error_arifmetic;
		return _container_amount.GetLastAddressPoint();
	}

	_static_stack = (*this);

	if ((*this)._tvar == chard)
		*(char*)(_static_stack._variable) += (*(char*)(value._variable));
	else if((*this)._tvar == intd)
		*(int*)(_static_stack._variable) += (*(int*)(value._variable));
	else if((*this)._tvar == doubled)
		*(double*)(_static_stack._variable) += (*(double*)(value._variable));

	_container_amount = _static_stack; //добавление нового элемента в контейнер
	//Такая технология как контейнеры хранения динамической памяти применяются здесь, для того, чтобы можно было осуществлять работу с памятью которая не удаляется
	//а остаётся на месте после выхода из метода-оператора, для дальнейшего использования этой памяти
	return _container_amount.GetLastAddressPoint(); //возвращается ссылка на последнюю добавленную память в контейнер _counter_amount (аналогично и с последующими операциями)
}

data_stack& data_stack::operator- (data_stack& value) {
	assert(_error == empty_error);

	data_stack _static_stack;

	if ((_variable == NULL) || ((_tvar != empty_type) && (_tvar != value._tvar)) || (value._variable == NULL) || (value._tvar == empty_type)) {
		_error = error_arifmetic;
		return _container_difference.GetLastAddressPoint();
	}

	_static_stack = (*this);

	if ((*this)._tvar == chard)
		*(char*)(_static_stack._variable) -= (*(char*)(value._variable));
	else if ((*this)._tvar == intd)
		*(int*)(_static_stack._variable) -= (*(int*)(value._variable));
	else if ((*this)._tvar == doubled)
		*(double*)(_static_stack._variable) -= (*(double*)(value._variable));

	_container_difference = _static_stack;

	return _container_difference.GetLastAddressPoint();
}

data_stack& data_stack::operator* (data_stack& value) {
	assert(_error == empty_error);

	data_stack _static_stack;

	if ((_variable == NULL) || ((_tvar != empty_type) && (_tvar != value._tvar)) || (value._variable == NULL) || (value._tvar == empty_type)) {
		_error = error_arifmetic;
		return _container_multiplication.GetLastAddressPoint();
	}

	_static_stack = (*this);

	if ((*this)._tvar == chard)
		*(char*)(_static_stack._variable) *= (*(char*)(value._variable));
	else if ((*this)._tvar == intd)
		*(int*)(_static_stack._variable) *= (*(int*)(value._variable));
	else if ((*this)._tvar == doubled)
		*(double*)(_static_stack._variable) *= (*(double*)(value._variable));

	_container_multiplication = _static_stack;

	return _container_multiplication.GetLastAddressPoint();
}

data_stack& data_stack::operator/ (data_stack& value) {
	assert(_error == empty_error);

	data_stack _static_stack;

	if ((_variable == NULL) || ((_tvar != empty_type) && (_tvar != value._tvar)) || (value._variable == NULL) || (value._tvar == empty_type)) {
		_error = error_arifmetic;
		return _container_multiplication.GetLastAddressPoint();
	}

	_static_stack = (*this);

	if ((*this)._tvar == chard) {
		if (!(*(char*)(value._variable))) {
			_error = error_arifmetic;
			return _container_division.GetLastAddressPoint();
		}
		*(char*)(_static_stack._variable) /= (*(char*)(value._variable));
	}
	else if ((*this)._tvar == intd) {
		if (!(*(int*)(value._variable))) {
			_error = error_arifmetic;
			return _container_division.GetLastAddressPoint();
		}
		*(int*)(_static_stack._variable) /= (*(int*)(value._variable));
	}
	else if ((*this)._tvar == doubled) {
		if (!(*(double*)(value._variable))) {
			_error = error_arifmetic;
			return _container_division.GetLastAddressPoint();
		}
		
		*(double*)(_static_stack._variable) /= (*(double*)(value._variable));
	}

	_container_division = _static_stack;

	return _container_division.GetLastAddressPoint();
}

data_stack& data_stack::operator^ (const short degree) {
	assert(_error == empty_error);

	data_stack _static_stack;

	if (_variable == NULL) {
		_error = error_arifmetic;
		return _container_exponentiation.GetLastAddressPoint();
	}

	_static_stack = (*this);

	if ((*this)._tvar == chard)
		*(char*)(_static_stack._variable) = TDegreeValue<char>((*(char*)(_static_stack._variable)), degree);
	else if ((*this)._tvar == intd)
		*(int*)(_static_stack._variable) = TDegreeValue<int>((*(int*)(_static_stack._variable)), degree);
	else if ((*this)._tvar == doubled)
		*(double*)(_static_stack._variable) = TDegreeValue<double>((*(double*)(_static_stack._variable)), degree);

	_container_exponentiation = _static_stack;

	return _container_exponentiation.GetLastAddressPoint();
}


void data_stack::SetNameVariable(char* name) {
	if (name == NULL)
		return;
	if (name_variable != NULL) {
		_error = error_redefination;
		return;
	}

	short k = StrLen(name);

	if (!NameVariableCheck(name)) {
		_error = error_name_variable;
		return;
	}

	name_variable = new char[(k + 1)];
	if (name_variable == NULL)
		assert(false);
	ZeroMemory(name_variable, (sizeof(char)*(k + 1)));

	for (short i = 0; i < k; i++)
		name_variable[i] = name[i];

	return;
}

void data_stack::GetNameVariable(char*& name) {
	if (name != NULL) {
		delete[] name;
		name = NULL;
	}

	short k = StrLen((*this).name_variable);
	name = new char[(k + 1)];
	if (name == NULL)
		assert(false);
	ZeroMemory(name, (sizeof(char)*(k + 1)));

	for (short i = 0; i < k; i++)
		name[i] = name_variable[i];

	return;
}

char* data_stack::GetPointerNameVariable() {
	return name_variable;
}

data_stack::type_error data_stack::GetError() {
	return _error;
}

void data_stack::SetSpecialError() {
	if (_error == empty_error)
		_error = error_special;

	return;
}

data_stack::type_data data_stack::GetTypeVariable() {
	return (*this)._tvar;
}
