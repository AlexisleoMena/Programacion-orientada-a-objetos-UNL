/*
Ejercicio 1. (30 pts) Escriba una funcion generica que reciba una secuencia de tipo list y un valor. La funcion debe devolver una nueva lista 
con los elementos menores al valor pasado como parametro. Escriba la porcion del programa cliente y el codigo necesario para poder invocar a 
la funcion usando datos de tipo string, float y un struct racional {int num,den;}
*/
#include <iostream>
#include <list>

using namespace std;

template<typename T>
list<T> Menores(const list<T> &L1, T valor) {
	list<T> L2;
	for(T Elemento : L1)
		if (Elemento<valor)
			L2.push_back(Elemento);
	return L2;
}
struct racional {
	int num, den;
};

bool operator < (racional A, racional B) { return A.num*B.den < B.num*A.den;}

int main() {
	list<float> L1 = { 0.72, 3.14, 1.76, 0.5 };
	auto L2 = Menores(L1,float(1.0));
	
	list<string> L3 = {"int","float","void","double"};
	auto L4 = Menores(L3,string("string"));
	
	list<racional> L5 = {{1,2},{3,4},{8,3}};
	auto L6 = Menores(L5,{5,8});
	
	return 0;
}
