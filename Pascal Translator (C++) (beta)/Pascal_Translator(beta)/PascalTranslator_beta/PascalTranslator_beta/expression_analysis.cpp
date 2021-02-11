#include "stdafx.h"
#include "expression_analysis.h"

expression_analysis::expression_analysis(){
}

expression_analysis::expression_analysis(begin_stack_end*& _b) {
	_bse = _b;
	assert(_bse != NULL);

	_text_exp = NULL;
	size_exp = 0;
	_text_code = NULL;
	size_code = 0;
	counter_exp = NULL;

	_error = error_empty;

	return;
}

expression_analysis::~expression_analysis(){
	_bse = NULL;
	if (_text_exp != NULL) {
		delete[] _text_exp;
		_text_exp = NULL;
	}
	size_exp = 0;

	if (_text_code != NULL) {
		delete[] _text_code;
		_text_code = NULL;
	}
	size_code = 0;
	counter_exp = 0;
	_error = error_empty;

	return;
}

void expression_analysis::PutCodeText(char* _text) {
	if ((_text == NULL) || (_text_code != NULL))
		return;
	CopyStr(_text, _text_code);
	assert(_text_code != NULL);

	size_code = StrLen(_text_code);
	assert(size_code);

	return;
}

void expression_analysis::FindNewExpression() {
	if (_text_code == NULL)
		return;
	short i = end;
	for (;( _text_code[i] != '=') && (i < size_code); i++);
	if (i >= size_code)
		return;

	short k = i;
	for (; ((_text_code[i] != ' ') && (_text_code[i] != '\n') && (i > 0)); i--);
	if (i < 0)
		return;

	begin = i;
	i = k;

	for (; ((_text_code[i] != ';') && (i < size_code)); i++);
	if (i >= size_code)
		return;

	end = i;

	short _ctsize = ((end - begin) + 2);
	char* _ctext = new char[_ctsize];
	ZeroMemory(_ctext, (sizeof(char)*_ctsize));

	for (short a = begin, b = 0; ((a <= end) && (b < _ctsize)); a++, b++)
		_ctext[b] = _text_code[a];

	if (_text_exp != NULL) {
		delete[] _text_exp;
		_text_exp = NULL;
	}

	CopyStr(_ctext, _text_exp);
	size_exp = StrLen(_text_exp);
	
	assert(_text_exp != NULL);

	delete[] _ctext;
	_ctext = NULL;

	return;
}

void expression_analysis::FindAllExpression() {
	if (_text_code == NULL)
		return;
	if (counter_exp)
		return;

	counter_exp = 0;
	for (short i = 0; i < size_code; i++)
		if ((_text_code[i] == ';') && (SymbolVariableCheck(_text_code[i - 1]) || (_text_code[i - 1] == ')')) && ((_text_code[i + 1] == ' ') || (_text_code[i + 1] == '\n')))
			counter_exp++;

	return;
}

bool expression_analysis::LowBracketCheck(short b, short e) {
	//задача этой функции: обобщённая обработка ошибок выражений вида +а)  и вида  (+а  соответственно
	if ((_text_exp == NULL) || (b >= e) || ((e - b - 1) < 1)) {
		_error = error_syntax;
		return false;
	}

	//b может указывать на арифметический символ, но тогда е указывает на символ закрывающей скобки
	//b может указывать на символ открывающей скобки, но тогда е указывает на арифметический символ
	//в противном случае это ошибка
	if ((SymbolArifmeticCheck(_text_exp[b]) && (_text_exp[e] == ')')) || ((_text_exp[b] == '(') && (SymbolArifmeticCheck(_text_exp[e])))) {
		if ((_text_exp[b + 1] == '.') || (_text_exp[e - 1] == '.')) {
			_error = error_syntax;
			return false;
		}
	}
	else {
		_error = error_syntax;
		return false;
	}

	bool t = true;

	bool var = false; //идентификатор того существует ли переменная в выражении
	for (short i = b; (i <= e) && (i < size_exp) && (!var); i++)
		if (SymbolVariableCheck(_text_exp[i]))
			var = true; //если встречен хоть один символ который можно использовать в имени переменной, то переменная существует.

	short cpoint = 0; //подсчёт точек
	short cval = 0; //подсчёт чисел
	short carfm = 0; //подсчёт арифметических операций
	for (short i = b; (i <= e) && (i < size_exp) && (t); i++) {
		if (_text_exp[i] == '.')
			cpoint++;
		if (SymbolValueCheck(_text_exp[i]))
			cval++;
		if (SymbolArifmeticCheck(_text_exp[i]))
			carfm++;
		if (!SymbolExpressionCheck(_text_exp[i]))
			t = false;
	}

	//в выражении типа (a+ , +a) может быть только одна операция, или только переменная или только число, и точка может быть только одна и только если есть число
	if (((cpoint >= 1) && (var)) || ((cval) && (var)) || (carfm != 1) || (!t)) {
		_error = error_syntax;
		return false;
	}

	if (var) {
		//проверка выражения на неправильные последовательности символов
		for (short i = b; (i <= (e - 1)) && (i < (size_exp - 1)) && (t); i++) {
			if ((SymbolVariableCheck(_text_exp[i])) && (!SymbolVariableCheck(_text_exp[i + 1])) 
				&& (!SymbolArifmeticCheck(_text_exp[i + 1])) && (!SymbolEquallyStr(_text_exp[i+1], const_cast<char*>("()"))))
				t = false;
			else if ((SymbolVariableCheck(_text_exp[i + 1])) && (!SymbolVariableCheck(_text_exp[i])) 
				&& (!SymbolArifmeticCheck(_text_exp[i])) && (!SymbolEquallyStr(_text_exp[i], const_cast<char*>("()"))))
				t = false;
		}

		if (!t) {
			_error = error_syntax;
			return false;
		}

		short var_b = 0, var_e = 0, var_i = b;
		for (; (!SymbolVariableCheck(_text_exp[var_i])) && (var_i <= e) && (var_i < size_exp); var_i++);
		if ((var_i > e) || (var_i >= size_exp)) {
			_error = error_syntax;
			t = false;
			return false;
		}
		var_b = var_i; //var_b - указывает на начало имени переменной

		for (; (SymbolVariableCheck(_text_exp[var_i])) && (var_i <= e) && (var_i < size_exp); var_i++);
		if ((var_i > e) || (var_i >= size_exp)) {
			_error = error_syntax;
			t = false;
			return false;
		}
		var_e = (var_i - 1); //var_e - указывает на конец имени переменной

		short _sztext = ((var_e - var_b) + 2);
		char* _ntext = new char[_sztext]; //в _ntext будет хранится имя переменной
		assert(_ntext != NULL);

		ZeroMemory(_ntext, (sizeof(char)*(_sztext)));

		for (short i = 0, j = var_b; ((i < (_sztext - 1)) && (j <= var_e)); i++, j++)
			_ntext[i] = _text_exp[j];

		t = (*_bse).FindVariable(_ntext);
		if (!t)
			_error = error_not_variable; //если переменной с таким именем в стеке нет, то это ошибка

		if (_ntext != NULL) {
			delete[] _ntext;
			_ntext = NULL;
		}
	}

	return t;
}

bool expression_analysis::LocalBracketCheck(short b, short e) {
	//проверка ориентирована чисто на выражения вида (<argument> <afirmetical_operation> <argument>)
	//это не совсем правильный подход, поскольку будут выражения и типа ((a+b)+c)
	//можно сделать так, чтобы проверка независела от скобок
	//т.е. выражение (((((а+и)+9)+ф)+з)+10) проверялось поэтапно по мере встречаемости символа - ( или любого другого арифметического оператора и проверка шла до
	//символа - ), по при этом с таким же успехом обрабатывалось выражение ((а+и)+(с+п)-(г*ф)), а также выражение простого вида (а+и)
	//но для этой обобщённой работы этой функции, нужно чтобы на вход подавались части начала и конца специфичных фрагментов этих выражений
	//
	// для (((ф+и)+и)+9) это    (ф+и)   +и)   +9)
	//
	// для ((ф+а)+(н-е)+(ш+4)) это (ф+а)   (н-е)   (ш+4)
	//
	// для (а+(и+(4*м))) это (а+    (и+    (4*м)
	//
	// для (ф+и) это (ф+и)
	//
	//в данный момент эта функция работает исключительно с видом (ф+и)

	if ((_text_exp == NULL) || (b >= e) || ((e - b - 1) < 3)) {
		_error = error_syntax;
		return false;
	}
	if (((_text_exp[b] == '(') && (_text_exp[e] == ')')) && ((_text_exp[b + 1] == '.') || (_text_exp[e - 1] == '.'))) {
		_error = error_syntax;
		return false;
	}

	short _lbcsize = ((e - b) + 2);
	char* _lbctext = new char[_lbcsize];
	ZeroMemory(_lbctext, (sizeof(char)*_lbcsize));

	for (short i = 0, j = b; ((i < (_lbcsize - 1)) && (j <= e)); i++, j++)
		_lbctext[i] = _text_exp[j];

	bool t = true;
	for (short i = 0; (i < (_lbcsize - 1)) && (t); i++)
		if ((!SymbolExpressionCheck(_lbctext[i])) || (SymbolEquallyStr(_lbctext[i], const_cast<char*>("=;:"))))
			t = false;
	if (!t) {
		_error = error_syntax;
		if (_lbctext != NULL) {
			delete[] _lbctext;
			_lbctext = NULL;
		}

		return false;
	}

	//variable check

	short counter_variable = 0;
	for(short i=0;i<(_lbcsize-1);i++)
		if (SymbolVariableCheck(_lbctext[i])) {
			for (; SymbolVariableCheck(_lbctext[i]); i++);
			counter_variable++;
		}

	//чисто математическая проверка навскидку..   begin (проверка точек)

	short point = 0;
	for (short i = 0; i < (_lbcsize - 1); i++)
		if (_lbctext[i] == '.')
			point++;

	if (((counter_variable == 2) && (point)) || ((counter_variable == 1) && (point > 1)) || ((!counter_variable) && (point > 2)))
		t = false;

	if (!t) {
		_error = error_syntax;
		if (_lbctext != NULL) {
			delete[] _lbctext;
			_lbctext = NULL;
		}

		return false;
	}

	//											  end (математическая проверка)

	if (point) {
		short i_arfm = 0;
		for (; (!SymbolArifmeticCheck(_lbctext[i_arfm])) && (i_arfm < (_lbcsize - 1)); i_arfm++);

		if ((i_arfm >= (_lbcsize - 1)) || (_lbctext[i_arfm - 1] == '.') || (_lbctext[i_arfm + 1] == '.')) { //***
			_error = error_syntax;
			if (_lbctext != NULL) {
				delete[] _lbctext;
				_lbctext = NULL;
			}

			t = false;
			return false;
		}
	}

	//											  end (проверка точек)

	for (short i = 0; ((i < (_lbcsize - 2)) && (t)); i++) {
		if ((SymbolVariableCheck(_lbctext[i])) && (!SymbolVariableCheck(_lbctext[i + 1]))
			&& (!SymbolArifmeticCheck(_lbctext[i + 1])) && (!SymbolEquallyStr(_lbctext[i + 1], const_cast<char*>("()"))))
			t = false;
		else if ((SymbolVariableCheck(_lbctext[i + 1])) && (!SymbolVariableCheck(_lbctext[i]))
			&& (!SymbolArifmeticCheck(_lbctext[i])) && (!SymbolEquallyStr(_lbctext[i], const_cast<char*>("()"))))
			t = false;
	}

	if (!t) {
		_error = error_syntax;
		if (_lbctext != NULL) {
			delete[] _lbctext;
			_lbctext = NULL;
		}

		return false;
	}

	if (counter_variable) {
		short var_i = 0;
		while ((counter_variable > 0) && (t)) {
			short var_b = 0, var_e = 0;
			for (; ((var_i < (_lbcsize - 1)) && (!SymbolVariableCheck(_lbctext[var_i]))); var_i++);
			if (var_i >= (_lbcsize - 1)) {
				_error = error_system;
				t = false;
				break;
			}
			var_b = var_i;

			for (; ((var_i < (_lbcsize - 1)) && (SymbolVariableCheck(_lbctext[var_i]))); var_i++);
			if (var_i >= (_lbcsize - 1)) {
				_error = error_system;
				t = false;
				break;
			}
			var_e = (var_i - 1);

			short _szwtext = ((var_e - var_b) + 2);
			char* _wtext = new char[_szwtext];
			assert(_wtext != NULL);

			ZeroMemory(_wtext, (sizeof(char)*(_szwtext)));

			for (short i = 0, j = var_b; (i < (_szwtext - 1)) && (j <= var_e); i++, j++)
				_wtext[i] = _lbctext[j];

			t = (*_bse).FindVariable(_wtext);

			if (_wtext != NULL) {
				delete[] _wtext;
				_wtext = NULL;
			}

			if (!t) {
				_error = error_not_variable;
				break;
			}

			counter_variable--;
		}
	}

	if (_lbctext != NULL) {
		delete[] _lbctext;
		_lbctext = NULL;
	}

	return t;
}

bool expression_analysis::BracketCheck() {
	if ((_text_exp == NULL) || (begin < 0) || (end < 0) || (begin >= end)) {
		_error = error_syntax;
		return false;
	}
	//предполагается что данная функция будет вызываться только в фунции ExpressionCheck() (т.е. те проверки что там есть уже пройдены)
	//(((a+b) + 5) + 8); - 3 операции и 6 скобок (математическая проверка)
	//((a+b) + (f+4) + (е+9)); - то же самое

	short counter_op = 0;
	short counter_bracket = 0;
	for (short i = 0; i < size_exp; i++) {
		if (SymbolArifmeticCheck(_text_exp[i]))
			counter_op++;
		if (SymbolEquallyStr(_text_exp[i], const_cast<char*>("()")))
			counter_bracket++;
	}

	//если общее число арифметических операций в выражении умноженное на 2 не даёт общего числа скобок в выражении вида ( и ), то это ошибка
	//если общее число арифметических операций в сумме с 3-ой не даёт общего числа скобок в выражении вида ( и ), то это ошибка
	if (((counter_op + 3) != counter_bracket) && ((counter_op*2) != counter_bracket)) { //чисто математическая проверка
		_error = error_syntax;
		return false;
	}

	short b_point = begin; //b_point в дальнейшем будет служить идентификатором префикса начала выражения (символ : )

	for (; (b_point <= end) && (b_point < size_exp) && (_text_exp[b_point] != ':'); b_point++);
	if ((b_point > end) || (b_point >= size_exp)) {
		_error = error_syntax;
		return false;
	}

	short e_point = (end-1);
	short true_bracket = 0;

	//Какая тут заложена идея и для каких скобок осуществляется эта проверка:
	//b_point и e_point являются индексами символьного массива указывающие на элементы массива равные символам ( и ) соответственно.
	//цикл работает до тех пор, пока b_point не равен e_point, и длина выражения в скобках больше или равна 3 (мин. такое выражение - (a+b)),
	//а также e_point больше начала самого выражения и b_point меньше конца выражения (это уже числовые рамки анализируемой модели).

	//Этот цикл годен только для проверки выражений типа ((а+и)+в) или (а+(в+и)), но не выражений типа ((a+b)+(c+d))
	//а также этот цикл не годен для проверки гибридных выражений типа (((a+b)+c)+(d+e)), ((a+b)+(d+(f+r)))
	while ((b_point != e_point) && ((e_point - b_point - 1) >= 3) && (e_point > begin) && (b_point < end)) {
		if ((_text_exp[e_point] == '(')) //если e_point нашла символ ( раньше чем b_point нашёл бы этот символ, то это ошибка и нужно осуществить выход из цикла
			break;

		if ((_text_exp[b_point] == '(') && (_text_exp[e_point] == ')')) {
			//если скобка найдена, такая что есть открывающая скобка ( и закрывающая скобка )
			//то это правильная скобка и бы повышаем счётчик правильных скобок на 1
			true_bracket++;
			//а также смещаем b_point вправо, а e_point влево по отрезку символьного массива формирующего выражение
			b_point++;
			e_point--;
		}
		
		if ((_text_exp[b_point] != '(')) //если b_point не указывает на элемент массива содержащего знак (, то смещаем b_point вправо по отрезку массива 
			b_point++;
		if ((_text_exp[e_point] != ')')) //если e_point не указывает на элемент массива содержащего знак ), то смещаем e_point влево по отрезку массива 
			e_point--;
	}

	bool t = true;

	if (true_bracket != counter_op) {
		//здесь осуществляется проверка выражений типа ((a+b)+(c+d))
		true_bracket = 0;
		short pb = begin;

		for (; (pb <= end) && (pb < size_exp) && (_text_exp[pb] != ':'); pb++);
		if ((pb > end) || (pb >= size_exp)) {
			_error = error_syntax;
			return false;
		}
		short pe = 0;
		pb++;

		for (; (pb <= end) && (pb < size_exp) && (_text_exp[pb] == '('); pb++);
		if ((pb > end) || (pb >= size_exp)) {
			_error = error_syntax;
			return false;
		}

		pb--; //pb указывает на индекс массива элемент которого равен символу (, но эта скобка начала выражения с которого начинается внутреннее выражение скобок ( )
		pe = pb;
		while ((pe < end) && (pe < size_exp)) {
			if (_text_exp[pb] != '(') {
				//если не найден символ (, то смещаем pb вправо по отрезку массива
				pb++;
				pe = pb;
			}

			if ((_text_exp[pe] != ')') && (_text_exp[pb] == '(')) //если pb указывает на элемент массива имеющий значение (, а pe не указывает на значение ), то pe смещается вправо
				pe++;

			if ((_text_exp[pb] == '(') && (_text_exp[pe] == ')')) {
				//Когда pb и pe указывают на отрезок скобки вида (a+b), то идёт проверка длины выражения в скобках.
				//Если длина выражения в скобках меньше 3, то это ошибка и следовательно нужно выйти из функции занеся данные об ошибке в атрибут класса
				if ((pe - pb - 1) < 3) {
					_error = error_syntax;
					return false;
				}

				true_bracket++; //если ошибки нет, то увеличиваем число правильных скобок
				pb++;
				pe = pb;
			}
		}

		//Если математическая проверка не прошла успешно, не делаем поспешных выводов об ошибке.
		//Возможно это гибридное выражение вида (((a+b)+c)+(d+3)), ((a+b)+(c+(d+(e+f))))
		//проверка которого будет осуществлена последней. И нужно её ДОПИСАТЬ!
		if ((counter_op - true_bracket) != (true_bracket - 1)) 
			t = false;
	}

	//ЗАДАЧА: Дописать проверку гибридного выражения вида (((a+b)+c)+(d+3)), ((a+b)+(c+(d+(e+f))))

	return true;
}

bool expression_analysis::ExpressionCheck() {
	//Что делает проверка:
	//проверяет определены ли переменные в выражении
	//проверяет корректность именования переменных
	//проверяет корректность всего выражения (без знаков табуляции и без запрещёных в выражении символов)

	//каких проверок ещё не хватает:
	//проверка на количество скобок и операций
	//проверка на корректное расположение скобок
	//проверка на типы аргументов которые входят в арифметические операции
	
	if ((_text_exp == NULL) || (begin < 0) || (end < 0) || (begin >= end)) {
		_error = error_syntax;
		return false;
	}

	if ((_text_exp[end] != ';') || (_text_exp[end-1] != ')')) {
		_error = error_syntax;
		return false;
	}
	bool t = true;

	//выражение не должно содержать пробелы и переход на новую строку
	//пример:   a=:((4+a)+9); 
	for (short i = 0; (i < size_exp) && (t); i++)
		if ((_text_exp[i] == ' ') || (_text_exp[i] == '\n') || (!SymbolExpressionCheck(_text_exp[i])))
			t = false;

	if (!t) {
		_error = error_syntax;
		return false;
	}

	short b = begin;
	short p = b;
	for (; (_text_exp[p] != '=') && (p < end); p++);
	if (_text_exp[p + 1] != ':') {
		_error = error_syntax;
		return false;
	}

	if ((p >= end) || (_text_exp[p+2] != '(')) {
		_error = error_syntax;
		return false;
	}
	p--;

	short _sztext = ((p - b) + 2);
	char* _nvar = new char[_sztext]; //+ _nvar содержит имя переменной которой будет присвоено значение выражения
	assert(_nvar != NULL);

	ZeroMemory(_nvar, (sizeof(char)*(_sztext)));

	for (short i = 0, r = b; (i < (_sztext-1)) && (r <= p); i++, r++) //***
		_nvar[i] = _text_exp[r];

	for (short i = 0; (i < (_sztext - 1)) && (t); i++)
		if (!SymbolVariableCheck(_nvar[i]))
			t = false;

	if (!t) {
		if (_nvar != NULL) { //-
			delete[] _nvar;
			_nvar = NULL;
		}
		_error = error_syntax;
		return false;
	}

	t = (*_bse).FindVariable(_nvar);
	if (!t) { //присвоение значения переменной которая не была определена или объявлена - это ошибка
		if (_nvar != NULL) { //-
			delete[] _nvar;
			_nvar = NULL;
		}
		_error = error_not_variable;
		return false;
	}

	if (_nvar != NULL) { //-
		delete[] _nvar;
		_nvar = NULL;
	}
	
	p += 2; //p указывает на символ открывающей скобки (при правильном выражении)
	for (short h = p; ((h < end) && (t)); h++) //переменные с именами вида af21af, 12asgfa запрещены
		if ((SymbolVariableCheck(_text_exp[h]) && SymbolValueCheck(_text_exp[h + 1]))
			|| (SymbolValueCheck(_text_exp[h]) && SymbolVariableCheck(_text_exp[h + 1]))
			|| ((_text_exp[h] == ')') && (_text_exp[h + 1] == '('))
			|| ((_text_exp[h] == '(') && (_text_exp[h + 1] == ')')))
			t = false;

	if (!t) {
		_error = error_syntax;
		return false;
	}

	short counter_var = 0; //количество переменных используемых в выражении
	for (short h = p; (h < end); h++)
		if (SymbolVariableCheck(_text_exp[h])) {
			h++;
			for (; SymbolVariableCheck(_text_exp[h]); h++);
			counter_var++;
		}

	while (counter_var) {
		//проверка на определение переменных
		short q = 0, w = 0; //q и w - индексы начала и конца имени переменной
		//p здесь является указателем с помощью которого мы без ошибок проходим весь отрезок массива находя при этом имена переменных
		//с последующей возможностью их проверки на хранение в стеке
		for (; (!SymbolVariableCheck(_text_exp[p]) && (p < end)); p++);
		if (p >= end) {
			t = false;
			break;
		}

		q = p;

		for (; (SymbolVariableCheck(_text_exp[p]) && (p < end)); p++);
		if (p >= end) {
			t = false;
			break;
		}

		w = (p - 1);
		short _dsize = ((w - q) + 2);
		char* _dtext = new char[_dsize]; //+
		assert(_dtext != NULL);

		ZeroMemory(_dtext, (sizeof(char)*_dsize));

		for (short i = 0, v = q; (i < (_dsize-1)) && (v <= w); i++, v++)
			_dtext[i] = _text_exp[v];

		if (!(*_bse).FindVariable(_dtext)) { //если в выражении появилась переменная которая ранее не была определена
			if (_dtext != NULL) { //-
				delete[] _dtext;
				_dtext = NULL;
			}
			t = false;
			_error = error_not_variable; //то это ошибка, и следовательно дальше ходу нет.
			break;
		}

		if (_dtext != NULL) { //-
			delete[] _dtext;
			_dtext = NULL;
		}

		counter_var--; //после проверки каждой переменной счётчик переменных уменьшается
	}

	t = (*this).BracketCheck(); //проверка на скобки различного вида (отсутствует определение проверки для гибридного выражения)
	if (!t) {
		_error = error_syntax;
		return false;
	}

	//после проверки скобок идёт проверка корректности написания самого выражения
	short idt = begin;
	while ((idt < end) && (t)) {
		short br_begin = 0, br_end = 0;

		//если br_begin указывает на индекс элемента массива значение которого равно скобки открывающей выражение - (
		//то br_end обязательно будет равен индексу элемента массива значение которого равно арифметической операции из определённого набора
		//если же _text_exp[br_begin] == '(', то _text_exp[br_end] обязательно будет равен арифметической операции из определённого набора
		for (; (idt < end) && (idt < size_exp); idt++) {
			if ((_text_exp[idt] == '(') || (SymbolArifmeticCheck(_text_exp[idt])))
				br_begin = idt;
			else if ((br_begin) && ((_text_exp[idt] == ')') || (SymbolArifmeticCheck(_text_exp[idt])))) {
				br_end = idt;
				break;
			}
		}

		if ((idt >= end) && (!br_end))
			break;
		
		t = (*this).LowBracketCheck(br_begin, br_end);

		idt++;
	}
	if (!t)
		_error = error_syntax;

	return t;
}
