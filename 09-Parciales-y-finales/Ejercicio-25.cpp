/*
Ejercicio 3 (25 pts) 
a) Escriba un funcion generica del_maxmin que reciba un vector de elementos del tipo generico y elimine del mismo tanto
el maximo elemento como el minimo. Si alguno de estos valores a eliminar esta repetido, debe eliminarlo todas las veces que aparezca. 
b) Implemente ademas un programa cliente que genere dos vectores, uno de enteros y otro de strings, y pruebe la funcion con ambos, mostrando 
en pantalla los vectores antes y despues de invocar a la funcion.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

struct persona{
	string nombre; 
	int edad;
};

bool operator < (const persona &A,const persona &B) { return A.nombre < B.nombre;}
bool operator > (const persona &A,const persona &B) { return A.nombre > B.nombre;}
bool operator == (const persona &A,const persona &B) { return A.nombre == B.nombre;}
ostream &operator <<(ostream &o,const persona &A){ o<<A.nombre; return o;}

template<typename C, typename E>
void del_maxmin(C &Contenedor){
	E maximo  = *max_element(Contenedor.begin(), Contenedor.end());
	E minimo  = *min_element(Contenedor.begin(), Contenedor.end());
	auto it = remove_if(Contenedor.begin(), Contenedor.end(), [&maximo, &minimo] (const E &A){return A == maximo or A == minimo;});
	/*Funcion lambda: funcion anonima o sin nombre creada en tiempo de ejecucion
	
	int Maximo = 30, int Minimo = 1;
	auto Coinciden = [&Maximo] (int valor) -> bool { return valor == Maximo or valor == Minimo;};   //function<bool(int)> Coinciden + #include <funtional>
	cout<<Coinciden(30); //Imprime 1 
	
	[] parametros de captura, la funcion puede tomar variables de todo su entorno (todo el ambito donde lambda fue declarada) y
	capturarlas para su cuerpo. Tambien puede tomar todo lo del ambito previamente definido por referencia [&] o por copia [=]
	() parametros formales
	-> es opcional, se escribe despues de parametros formales para indicando el tipo de retorno
	*/
	Contenedor.erase(it,Contenedor.end());
}

template<typename C, typename E>
void Mostrar_contenedor(const C &Contenedor){
	cout<<"Contenedor: ";
	for(E elemento : Contenedor)
		cout<<elemento<<" ";
	cout<<endl;
}
int main() {
	vector<int> V = {1,1,1,2,3,4,5,6,9,9,9,7};
	del_maxmin<vector<int>,int>(V);
	Mostrar_contenedor<vector<int>,int>(V);
	
	list<string> L = {"Alexis","Alexis","Walter","Kevin","Juan","Carlos"};
	del_maxmin<list<string>, string>(L);
	Mostrar_contenedor<list<string>,string>(L);
	
	list<persona> L1 = {{"Alexis",11},{"Alexis",33},{"Juan",32}, {"Kevin",11}, {"Walter",12}};
	del_maxmin<list<persona>,persona>(L1);
	Mostrar_contenedor<list<persona>,persona>(L1);
	return 0;
}

