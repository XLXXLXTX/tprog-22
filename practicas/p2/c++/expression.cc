#include "expression.h"
#include <iostream>
#include <sstream>

using namespace std;

void Expression::parse(const string& s)
{
	istringstream ss(s);
	string tok;

	// Pila de términos
	// Consulta el tipo de datos 'stack' de la STL
	???? stk;

	while (ss >> tok)
	{
		if (tok=="+")
		{
			// Apilar suma
			...
		}
		else if (tok=="-")
		{
			// Apilar resta
			...
		}
		else if (tok=="*")
		{
			// Apilar producto
			...
		}
		else if (tok=="/")
		{
			// Apilar cociente
			...
		}
		else
		{
			// Variable o constante
			// Si comienza por un caracter no numerico,
			// es un nombre de variable
			if (isalpha(tok[0]))
			{
				// Apilar variable
				...
			}
			else
			{
				float f = stof(tok);
				// Apilar constante
				...
			}
		}
	}

	root = // cima de la pila
}

float Expression::eval(const SymbolTab& syms) const
{
	// Devuelve el resultado de evaluar la expresion
}

string Expression::to_string() const
{
	// Devuelve la cadena que representa la expresion
}

ostream& operator<<(ostream& os,const Expression& e)
{
    os << e.to_string();

    return os;
}

