#pragma once

#include <iostream>

class Expression
{
private:
	// Raiz del arbol de terminos
	???? root;

	void	parse(const string& s);

	string to_string() const;

public:
	// Cnstructores
	....

	float	eval(const SymbolTab& syms) const;

	friend ostream& operator<<(ostream& os,const Expression& e);
};

ostream& operator<<(ostream& os,const Expression& e);
