/*
Ejercicio 1 (30pts). Escriba una funcion generica que reciba 4 argumentos: una secuencia de tipo list L, un valor X y dos valores enteros 
correspondientes a las posiciones (en base 0) de comienzo y final de un intervalo en la lista. La funcion debe retornar la cantidad de 
elementos con valor X que se encuentran en dicho intervalo. Escriba la porcion del programa cliente y codigo necesario para poder invocar 
a la funcion usando datos de tipo string, int y un struct complejo {int pr, pi}. Por ejemplo, si la funcion recibe una lista de 
enteros L=[8, 24, 31, 42, 78, 42, 30, 32, 42, 23, 42] y los valores X=42, comienzo=1, fin=6 el resultado debe ser 2.
*/

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

struct complejo { 
	int Re, Im; 
};

bool operator == (const complejo &A, const complejo &B) { return (A.Re == B.Re) and (A.Im == B.Im);}

template<typename T>
int contar(list<T> L, T valor, int ini, int fin) {
	/*auto it_begin = L.begin(), it_end = L.begin();
	advance(it_begin, ini);
	advance(it_end, fin+1);
	return count(it_begin, it_end, valor);*/
	return count(next(L.begin(),ini), next(L.begin(),fin+1), valor);	
}
int main() {
	list<int> L1 = {8, 24, 42, 56, 67, 42, 30, 32, 42, 23, 42};
	cout << "El valor 42 en [1,6] esta: " << contar(L1,42,1,6) << " veces\n";
	
	list<string> L2 = {"gato", "perro", "perro", "conejo", "conejo", "perro", "caballo", "perro", "gato", "conejo", "perro"};
	cout << "El valor 'perro' en [1,7] esta: " << contar(L2,"perro"s,1,7) << " veces\n";;
	
	list<complejo> L3 = {{8,0}, {4,2}, {3,1}, {4,2}, {7,8}, {4,2}, {3,0}, {3,2}, {4,2}, {2,3}, {4,2}};
	cout << "El valor 4+2i en [1,6] esta: " << contar(L3,{4,2},1,6) << " veces\n";
	
	return 0;
}
