#include "static-stack.h"
#include "dynamic-stack.h"
#include <iostream>

// TODO: Define la cabecera de esta función mediante programacion generica para
// que sea equivalente a declarar las dos funciones siguientes:
//
// void anyadir_elementos(static-stack<int>& stk)
// void anyadir_elementos(dynamic-stack<int>& stk)
// ... anyadir_elementos ...
template<typename T>
void anyadir_elementos(T& stk)
{
	stk.push(42);
	stk.push(15);
	stk.pop();
	for (int i=0; i<100; i+=5)
		stk.push(i);
}

//TODO: Define la cabecera de esta función mediante programacion generica para
//que sea equivalente a declarar las dos funciones siguientes:
//
//void mostrar_elementos(const static_stack<int>& stk)
//void mostrar_elementos(const dynamic_stack<int>& stk)
// ... mostrar_elementos ...

template<typename T>
void mostrar_elementos(const T& stk)
{
	for (int i : stk)
		std::cout << i << " ";
	std::cout << std::endl;
}

int main(int argc,char* argv[])
{
	static_stack<int>  s_stk;
	dynamic_stack<int> d_stk;

	anyadir_elementos(s_stk);
	anyadir_elementos(d_stk);

	mostrar_elementos(s_stk);
	mostrar_elementos(d_stk);

	return 0;
}
