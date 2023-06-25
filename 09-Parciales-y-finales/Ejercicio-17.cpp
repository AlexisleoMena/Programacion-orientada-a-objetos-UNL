/*
Ejercicio 1 [30 pts] Escriba una función genérica (template) llamada ampliar() que reciba como
argumentos un objeto llamado archname de tipo string y un arreglo de la clase vector (STL) llamado x
que contiene structs de 2 miembros: valor (genérico) y pos (char). El string archname corresponde al
nombre de un archivo binario. La función debe agregar al archivo el dato (valor) de cada elemento del
arreglo x. Los agregados se hacen al principio del archivo si pos contiene ‘f’ y al final del archivo si
pos contiene ‘b’. 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

template<typename T>
struct Elemento{
	T valor;
	char pos;
};

template<typename C, typename E>
void ampliar(string archname, C Contenedor){
	for(auto it = Contenedor.begin(); it != Contenedor.end(); ++it){
		auto it_b = find_if(it, Contenedor.end(), [] (const Elemento<E> &A) { return A.pos == 'b';});
		if(it_b != Contenedor.end())
			rotate(it, it_b, next(it_b)); //it: Nueva ubicaci�n del primer elemento del conjunto de elementos que se rotar�n (siempre menor a it_b); it_b: primer elemento del conjunto; next(it_b): una posicion m�s all� del �ltimo elemento del conjunto que se rotar�
	}
	//reverse(Contenedor.begin(), Contenedor.end()) si quiero poner elementos con 'b' al final o rotate(it_b, next(it_b), Contenedor.end());
	ofstream archi_out(archname, ios::binary|ios::trunc);
	for(Elemento<E> i: Contenedor)
		archi_out.write(reinterpret_cast<char*> (&i), sizeof(i));
	archi_out.close();
}

template<typename T>
void Mostrar(string archname){
	ifstream archi_in(archname, ios::binary|ios::in|ios::ate);
	int n = archi_in.tellg()/sizeof(Elemento<T>);
	archi_in.seekg(0);
	for(int i=0; i<n; ++i){
		Elemento<T> A;
		archi_in.read(reinterpret_cast<char*> (&A), sizeof(A));
		cout<<A.pos<<" "<<A.valor<<endl;
	}
}

int main() {
	string archname = "Ejercio1.dat";
	vector<Elemento<int>> V = {{1,'f'},{2,'b'},{3,'f'},{4,'f'},{5,'b'},{6,'b'}};
	ampliar<vector<Elemento<int>>,int>(archname,V);
	Mostrar<int>(archname);
	return 0;
}

