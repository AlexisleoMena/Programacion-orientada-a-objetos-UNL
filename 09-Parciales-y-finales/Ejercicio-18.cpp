/*
Ejercicio 1 [25 pts] Escriba una función genérica para cualquier tipo de elemento llamada
vector_a_lista(...) que reciba un std::vector y retorne una std::list que contenga los elementos del vector
de entrada, sin repetidos. Debe mantener el orden del vector. Escriba un programa cliente que genere
un vector con 40 enteros aleatorios, utilice la función para pasarlos a una lista, y muestre la lista en
pantalla.
*/
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

template<typename C1, typename C2>
C2 vector_lista(C1 &Contenedor){
	for(auto it = Contenedor.begin(); it != Contenedor.end(); ++it){
		auto it_rep = remove(next(it), Contenedor.end(), *it);
		Contenedor.erase(it_rep, Contenedor.end());
	}
	C2 Nuevo_Contenedor;
	for(auto it = Contenedor.begin(); it!= Contenedor.end(); ++it)
		Nuevo_Contenedor.push_back(*it);
	return Nuevo_Contenedor;
}

template<typename C>
void Mostrar_contenedor(const C &Contenedor){
	cout<<"Contenedor: ";
	for(auto it: Contenedor)
		cout<<it<<" ";
	cout<<endl;
}

int main() {
	list<int> L = {1,2,3,4,4,6,7,7,7,7,8};
	vector<int> V = vector_lista<list<int>,vector<int>>(L);
	Mostrar_contenedor(V);
	
	vector<int> V1 = {1,1,1,2,2,2,3,4,5,6,7,7,8,9};
	list<int> L1 = vector_lista<vector<int>,list<int>>(V1);
	Mostrar_contenedor(L1);
	return 0;
}

