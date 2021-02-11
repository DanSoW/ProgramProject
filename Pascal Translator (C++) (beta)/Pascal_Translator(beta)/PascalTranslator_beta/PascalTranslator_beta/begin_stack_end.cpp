#include "stdafx.h"
#include "begin_stack_end.h"


begin_stack_end::begin_stack_end(){
	_vstack = NULL;
	size_stack = 0;

	return;
}


begin_stack_end::~begin_stack_end(){
	if (_vstack != NULL) {
		delete[] _vstack;
		_vstack = NULL;
	}
	size_stack = 0;

	return;
}

void begin_stack_end::PutVariable(char* name, data_stack::type_data _vtype) {
	if (_vstack == NULL) {
		size_stack = 1;
		_vstack = new data_stack[size_stack];
		_vstack[0].SetNameVariable(name);

		if (_vtype == data_stack::chard)
			_vstack[0] = (char)(0);
		else if (_vtype == data_stack::intd)
			_vstack[0] = (int)(0);
		else if (_vtype == data_stack::doubled)
			_vstack[0] = (double)(0);

		return;
	}

	data_stack* _copy_stack = new data_stack[(size_stack + 1)];
	if (_copy_stack == NULL)
		assert(false);

	for (short i = 0; i < size_stack; i++){
		_copy_stack[i] = _vstack[i];
		_copy_stack[i].SetNameVariable(_vstack[i].GetPointerNameVariable());
	}

	_copy_stack[size_stack].SetNameVariable(name);

	if (_vtype == data_stack::chard)
		_copy_stack[size_stack] = (char)(0);
	else if (_vtype == data_stack::intd)
		_copy_stack[size_stack] = (int)(0);
	else if (_vtype == data_stack::doubled)
		_copy_stack[size_stack] = (double)(0);

	delete[] _vstack;
	_vstack = NULL;

	_vstack = _copy_stack;
	size_stack++;

	return;
}

bool begin_stack_end::FindVariable(char* name) {
	if ((_vstack == NULL) || (name == NULL))
		return false;

	bool t = false;

	if (!NameVariableCheck(name)) {
		_error = error_name_var;
		return false;
	}

	for (short i = 0; (i < size_stack) && (!t); i++)
		if (StrEquallyStr(_vstack[i].GetPointerNameVariable(), name))
			t = true;

	return t;
}

bool begin_stack_end::FindVariable(char* name, short& index) {
	if ((_vstack == NULL) || (name == NULL))
		return false;

	bool t = false;
	index = 0;

	if (!NameVariableCheck(name)) {
		_error = error_name_var;
		return false;
	}

	for (short i = 0; (i < size_stack) && (!t); i++)
		if (StrEquallyStr(_vstack[i].GetPointerNameVariable(), name)) {
			index = i;
			t = true;
		}

	return t;
}

data_stack& begin_stack_end::GetVariable(char* name_var) {
	static data_stack _stack_null;
	_stack_null.SetSpecialError();

	if ((_vstack == NULL) || (name_var == NULL))
		return _stack_null;

	short index = 0;

	if (!(*this).FindVariable(name_var, index))
		return _stack_null;
	if (index < 0)
		return _stack_null;

	return _vstack[index];
}
