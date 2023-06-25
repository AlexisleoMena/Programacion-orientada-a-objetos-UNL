/*
Ejercicio 2 (35pts) Escriba una funcion generica llamada sublistado(..) que reciba un nombre de archivo y un dato X. 
La funcion debe cargar los datos del archivo y generar (y retornar) un vector con los elementos menores a X, ordenados en forma decreciente. 
Utilice la funcion en un programa C++, invocandola y utilizando como parametros de llamada: 
a) una lista de enteros cuyos datos se hallan en el archivo de texto "lista_int.txt" (un entero por linea), para obtener los enteros menores a 42; 
b) una lista de strings cuyos datos se hallan en el archivo "lista_str.txt" (una palabra por linea), para obtener los strings menores a "foo"; 
c) una lista de tipo Evento (struct con dia, mes, año, y descripcion) cuyos datos se hallan en el archivo "eventos.txt" (un evento por linea, los 4 campos separados por espacios), para obtener los eventos previos al 4 de mayo de 2021.
*/

#include <iostream>
#include <list>
#include <fstream>

using namespace std;

string random_string(){
	string palabra(3, ' ');
	for(char &letra: palabra)
		letra = 'a'+rand()%26;
	return palabra;
}
struct Evento{
	int dia, mes, anio;
	string descripcion;
};

ifstream &operator >> (ifstream &f, Evento &A){
	f>>A.dia>>A.mes>>A.anio;
	f.ignore();
	getline(f, A.descripcion);;
	return f;
}

ostream &operator << (ostream &o, Evento &A){
	o<<A.dia<<"/"<<A.mes<<"/"<<A.anio<<" "<<A.descripcion;
	return o;
}

bool operator < (Evento A, Evento B){
	int diasA = A.anio*365 + A.mes*30 + A.dia;
	int diasB = B.anio*365 + B.mes*30 + B.dia;
	return diasA<diasB;
}

template<typename T>
list<T> sublistado(string Nombre_archivo, T Elemento_x){
	ifstream f(Nombre_archivo);
	list<T> L;
	T Elemento_i;
	while(f>>Elemento_i)
		if(Elemento_i < Elemento_x)
			L.push_back(Elemento_i);
	L.sort();
	L.reverse();
	return L;
}
template<typename T>
void Mostrar(list<T> Contenedor){
	cout<<"\nMenores: ";
	for(T Elemento: Contenedor)
		cout<<Elemento<<" | ";
}

int main() {
	string Nombre_archivo1 = "lista_int.txt";
	string Nombre_archivo2 = "lista_str.txt";
	string Nombre_archivo3 = "eventos.txt";
	
	ofstream f1(Nombre_archivo1, ios::trunc);
	ofstream f2(Nombre_archivo2, ios::trunc);
	ofstream f3(Nombre_archivo3, ios::trunc);

	cout<<"Contenedor 1: ";
	for(int i=0; i<10; ++i){
		int entero = rand()%50; 
		f1<<entero<<endl;
		cout<<entero<<" ";
	}
	
	cout<<"\nContenedor 2: ";
	for(int i=0; i<7; ++i){
		string palabra = random_string(); 
		f2<<palabra<<endl;
		cout<<palabra<<" ";
	}
	cout<<"\nContenedor 3: ";
	cout<<"12/11/2012 Evento 1 09/10/2013 Evento 2 01/09/2021 Evento 3"<<endl;
	f3<<12<<" "<<11<<" "<<2012<<" Evento 1"<<endl;
	f3<<9<<" "<<10<<" "<<2013<<" Evento 2"<<endl;
	f3<<1<<" "<<9<<" "<<2021<<" Evento 3"<<endl;
	f1.close();
	f2.close();
	f3.close();
	
	list<int> L1 = sublistado<int>(Nombre_archivo1, 42);
	Mostrar(L1);
	
	list<string> L2 = sublistado<string> (Nombre_archivo2, "foo");
	Mostrar(L2);
	
	list<Evento> L3 = sublistado<Evento>(Nombre_archivo3, {4,5,2021,"NNN"});
	Mostrar(L3);
	return 0;
}

