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
	//������ ���� �������: ���������� ��������� ������ ��������� ���� +�)  � ����  (+�  ��������������
	if ((_text_exp == NULL) || (b >= e) || ((e - b - 1) < 1)) {
		_error = error_syntax;
		return false;
	}

	//b ����� ��������� �� �������������� ������, �� ����� � ��������� �� ������ ����������� ������
	//b ����� ��������� �� ������ ����������� ������, �� ����� � ��������� �� �������������� ������
	//� ��������� ������ ��� ������
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

	bool var = false; //������������� ���� ���������� �� ���������� � ���������
	for (short i = b; (i <= e) && (i < size_exp) && (!var); i++)
		if (SymbolVariableCheck(_text_exp[i]))
			var = true; //���� �������� ���� ���� ������ ������� ����� ������������ � ����� ����������, �� ���������� ����������.

	short cpoint = 0; //������� �����
	short cval = 0; //������� �����
	short carfm = 0; //������� �������������� ��������
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

	//� ��������� ���� (a+ , +a) ����� ���� ������ ���� ��������, ��� ������ ���������� ��� ������ �����, � ����� ����� ���� ������ ���� � ������ ���� ���� �����
	if (((cpoint >= 1) && (var)) || ((cval) && (var)) || (carfm != 1) || (!t)) {
		_error = error_syntax;
		return false;
	}

	if (var) {
		//�������� ��������� �� ������������ ������������������ ��������
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
		var_b = var_i; //var_b - ��������� �� ������ ����� ����������

		for (; (SymbolVariableCheck(_text_exp[var_i])) && (var_i <= e) && (var_i < size_exp); var_i++);
		if ((var_i > e) || (var_i >= size_exp)) {
			_error = error_syntax;
			t = false;
			return false;
		}
		var_e = (var_i - 1); //var_e - ��������� �� ����� ����� ����������

		short _sztext = ((var_e - var_b) + 2);
		char* _ntext = new char[_sztext]; //� _ntext ����� �������� ��� ����������
		assert(_ntext != NULL);

		ZeroMemory(_ntext, (sizeof(char)*(_sztext)));

		for (short i = 0, j = var_b; ((i < (_sztext - 1)) && (j <= var_e)); i++, j++)
			_ntext[i] = _text_exp[j];

		t = (*_bse).FindVariable(_ntext);
		if (!t)
			_error = error_not_variable; //���� ���������� � ����� ������ � ����� ���, �� ��� ������

		if (_ntext != NULL) {
			delete[] _ntext;
			_ntext = NULL;
		}
	}

	return t;
}

bool expression_analysis::LocalBracketCheck(short b, short e) {
	//�������� ������������� ����� �� ��������� ���� (<argument> <afirmetical_operation> <argument>)
	//��� �� ������ ���������� ������, ��������� ����� ��������� � ���� ((a+b)+c)
	//����� ������� ���, ����� �������� ���������� �� ������
	//�.�. ��������� (((((�+�)+9)+�)+�)+10) ����������� �������� �� ���� ������������� ������� - ( ��� ������ ������� ��������������� ��������� � �������� ��� ��
	//������� - ), �� ��� ���� � ����� �� ������� �������������� ��������� ((�+�)+(�+�)-(�*�)), � ����� ��������� �������� ���� (�+�)
	//�� ��� ���� ���������� ������ ���� �������, ����� ����� �� ���� ���������� ����� ������ � ����� ����������� ���������� ���� ���������
	//
	// ��� (((�+�)+�)+9) ���    (�+�)   +�)   +9)
	//
	// ��� ((�+�)+(�-�)+(�+4)) ��� (�+�)   (�-�)   (�+4)
	//
	// ��� (�+(�+(4*�))) ��� (�+    (�+    (4*�)
	//
	// ��� (�+�) ��� (�+�)
	//
	//� ������ ������ ��� ������� �������� ������������� � ����� (�+�)

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

	//����� �������������� �������� ���������..   begin (�������� �����)

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

	//											  end (�������������� ��������)

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

	//											  end (�������� �����)

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
	//�������������� ��� ������ ������� ����� ���������� ������ � ������ ExpressionCheck() (�.�. �� �������� ��� ��� ���� ��� ��������)
	//(((a+b) + 5) + 8); - 3 �������� � 6 ������ (�������������� ��������)
	//((a+b) + (f+4) + (�+9)); - �� �� �����

	short counter_op = 0;
	short counter_bracket = 0;
	for (short i = 0; i < size_exp; i++) {
		if (SymbolArifmeticCheck(_text_exp[i]))
			counter_op++;
		if (SymbolEquallyStr(_text_exp[i], const_cast<char*>("()")))
			counter_bracket++;
	}

	//���� ����� ����� �������������� �������� � ��������� ���������� �� 2 �� ��� ������ ����� ������ � ��������� ���� ( � ), �� ��� ������
	//���� ����� ����� �������������� �������� � ����� � 3-�� �� ��� ������ ����� ������ � ��������� ���� ( � ), �� ��� ������
	if (((counter_op + 3) != counter_bracket) && ((counter_op*2) != counter_bracket)) { //����� �������������� ��������
		_error = error_syntax;
		return false;
	}

	short b_point = begin; //b_point � ���������� ����� ������� ��������������� �������� ������ ��������� (������ : )

	for (; (b_point <= end) && (b_point < size_exp) && (_text_exp[b_point] != ':'); b_point++);
	if ((b_point > end) || (b_point >= size_exp)) {
		_error = error_syntax;
		return false;
	}

	short e_point = (end-1);
	short true_bracket = 0;

	//����� ��� �������� ���� � ��� ����� ������ �������������� ��� ��������:
	//b_point � e_point �������� ��������� ����������� ������� ����������� �� �������� ������� ������ �������� ( � ) ��������������.
	//���� �������� �� ��� ���, ���� b_point �� ����� e_point, � ����� ��������� � ������� ������ ��� ����� 3 (���. ����� ��������� - (a+b)),
	//� ����� e_point ������ ������ ������ ��������� � b_point ������ ����� ��������� (��� ��� �������� ����� ������������� ������).

	//���� ���� ����� ������ ��� �������� ��������� ���� ((�+�)+�) ��� (�+(�+�)), �� �� ��������� ���� ((a+b)+(c+d))
	//� ����� ���� ���� �� ����� ��� �������� ��������� ��������� ���� (((a+b)+c)+(d+e)), ((a+b)+(d+(f+r)))
	while ((b_point != e_point) && ((e_point - b_point - 1) >= 3) && (e_point > begin) && (b_point < end)) {
		if ((_text_exp[e_point] == '(')) //���� e_point ����� ������ ( ������ ��� b_point ����� �� ���� ������, �� ��� ������ � ����� ����������� ����� �� �����
			break;

		if ((_text_exp[b_point] == '(') && (_text_exp[e_point] == ')')) {
			//���� ������ �������, ����� ��� ���� ����������� ������ ( � ����������� ������ )
			//�� ��� ���������� ������ � �� �������� ������� ���������� ������ �� 1
			true_bracket++;
			//� ����� ������� b_point ������, � e_point ����� �� ������� ����������� ������� ������������ ���������
			b_point++;
			e_point--;
		}
		
		if ((_text_exp[b_point] != '(')) //���� b_point �� ��������� �� ������� ������� ����������� ���� (, �� ������� b_point ������ �� ������� ������� 
			b_point++;
		if ((_text_exp[e_point] != ')')) //���� e_point �� ��������� �� ������� ������� ����������� ���� ), �� ������� e_point ����� �� ������� ������� 
			e_point--;
	}

	bool t = true;

	if (true_bracket != counter_op) {
		//����� �������������� �������� ��������� ���� ((a+b)+(c+d))
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

		pb--; //pb ��������� �� ������ ������� ������� �������� ����� ������� (, �� ��� ������ ������ ��������� � �������� ���������� ���������� ��������� ������ ( )
		pe = pb;
		while ((pe < end) && (pe < size_exp)) {
			if (_text_exp[pb] != '(') {
				//���� �� ������ ������ (, �� ������� pb ������ �� ������� �������
				pb++;
				pe = pb;
			}

			if ((_text_exp[pe] != ')') && (_text_exp[pb] == '(')) //���� pb ��������� �� ������� ������� ������� �������� (, � pe �� ��������� �� �������� ), �� pe ��������� ������
				pe++;

			if ((_text_exp[pb] == '(') && (_text_exp[pe] == ')')) {
				//����� pb � pe ��������� �� ������� ������ ���� (a+b), �� ��� �������� ����� ��������� � �������.
				//���� ����� ��������� � ������� ������ 3, �� ��� ������ � ������������� ����� ����� �� ������� ������ ������ �� ������ � ������� ������
				if ((pe - pb - 1) < 3) {
					_error = error_syntax;
					return false;
				}

				true_bracket++; //���� ������ ���, �� ����������� ����� ���������� ������
				pb++;
				pe = pb;
			}
		}

		//���� �������������� �������� �� ������ �������, �� ������ ��������� ������� �� ������.
		//�������� ��� ��������� ��������� ���� (((a+b)+c)+(d+3)), ((a+b)+(c+(d+(e+f))))
		//�������� �������� ����� ������������ ���������. � ����� � ��������!
		if ((counter_op - true_bracket) != (true_bracket - 1)) 
			t = false;
	}

	//������: �������� �������� ���������� ��������� ���� (((a+b)+c)+(d+3)), ((a+b)+(c+(d+(e+f))))

	return true;
}

bool expression_analysis::ExpressionCheck() {
	//��� ������ ��������:
	//��������� ���������� �� ���������� � ���������
	//��������� ������������ ���������� ����������
	//��������� ������������ ����� ��������� (��� ������ ��������� � ��� ���������� � ��������� ��������)

	//����� �������� ��� �� �������:
	//�������� �� ���������� ������ � ��������
	//�������� �� ���������� ������������ ������
	//�������� �� ���� ���������� ������� ������ � �������������� ��������
	
	if ((_text_exp == NULL) || (begin < 0) || (end < 0) || (begin >= end)) {
		_error = error_syntax;
		return false;
	}

	if ((_text_exp[end] != ';') || (_text_exp[end-1] != ')')) {
		_error = error_syntax;
		return false;
	}
	bool t = true;

	//��������� �� ������ ��������� ������� � ������� �� ����� ������
	//������:   a=:((4+a)+9); 
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
	char* _nvar = new char[_sztext]; //+ _nvar �������� ��� ���������� ������� ����� ��������� �������� ���������
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
	if (!t) { //���������� �������� ���������� ������� �� ���� ���������� ��� ��������� - ��� ������
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
	
	p += 2; //p ��������� �� ������ ����������� ������ (��� ���������� ���������)
	for (short h = p; ((h < end) && (t)); h++) //���������� � ������� ���� af21af, 12asgfa ���������
		if ((SymbolVariableCheck(_text_exp[h]) && SymbolValueCheck(_text_exp[h + 1]))
			|| (SymbolValueCheck(_text_exp[h]) && SymbolVariableCheck(_text_exp[h + 1]))
			|| ((_text_exp[h] == ')') && (_text_exp[h + 1] == '('))
			|| ((_text_exp[h] == '(') && (_text_exp[h + 1] == ')')))
			t = false;

	if (!t) {
		_error = error_syntax;
		return false;
	}

	short counter_var = 0; //���������� ���������� ������������ � ���������
	for (short h = p; (h < end); h++)
		if (SymbolVariableCheck(_text_exp[h])) {
			h++;
			for (; SymbolVariableCheck(_text_exp[h]); h++);
			counter_var++;
		}

	while (counter_var) {
		//�������� �� ����������� ����������
		short q = 0, w = 0; //q � w - ������� ������ � ����� ����� ����������
		//p ����� �������� ���������� � ������� �������� �� ��� ������ �������� ���� ������� ������� ������ ��� ���� ����� ����������
		//� ����������� ������������ �� �������� �� �������� � �����
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

		if (!(*_bse).FindVariable(_dtext)) { //���� � ��������� ��������� ���������� ������� ����� �� ���� ����������
			if (_dtext != NULL) { //-
				delete[] _dtext;
				_dtext = NULL;
			}
			t = false;
			_error = error_not_variable; //�� ��� ������, � ������������� ������ ���� ���.
			break;
		}

		if (_dtext != NULL) { //-
			delete[] _dtext;
			_dtext = NULL;
		}

		counter_var--; //����� �������� ������ ���������� ������� ���������� �����������
	}

	t = (*this).BracketCheck(); //�������� �� ������ ���������� ���� (����������� ����������� �������� ��� ���������� ���������)
	if (!t) {
		_error = error_syntax;
		return false;
	}

	//����� �������� ������ ��� �������� ������������ ��������� ������ ���������
	short idt = begin;
	while ((idt < end) && (t)) {
		short br_begin = 0, br_end = 0;

		//���� br_begin ��������� �� ������ �������� ������� �������� �������� ����� ������ ����������� ��������� - (
		//�� br_end ����������� ����� ����� ������� �������� ������� �������� �������� ����� �������������� �������� �� ������������ ������
		//���� �� _text_exp[br_begin] == '(', �� _text_exp[br_end] ����������� ����� ����� �������������� �������� �� ������������ ������
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
