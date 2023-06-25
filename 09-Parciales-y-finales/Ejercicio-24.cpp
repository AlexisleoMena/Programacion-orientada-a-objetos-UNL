/*
Ejercicio 3 (35pts) Un archivo "resultados.dat" tiene los resultados de C carreras de Formula 1. Por cada carrera, hay 20 pares de datos
guardados con un struct Par{char nombre[50],int pos}, que registran el nombre y la posicion en que finalizo cada uno de los 20 pilotos en 
esa carrera (pueden estar en cualquier orden). Escriba una uncion void mejoresN(string nombre_archivo, int N) que lea los datos del archivo 
"resultados.dat" y luego haga lo siguiente: 
a) cargue todos los datos en un unico vector de pares, 
b) ordene los pares de cada carrera (de 20 en 20) por posicion; 
c) en cada carrera deje solo los N mejores corredores (elimine el resto, el vector final tendra (C*N pares); guarde el 
vector resultante en un archivo de texto cuyo nombre se recibio como parametro, poniendo antes de cada carrera el texto "Carrera #i:" 
(donde i es el numero de 1 a C) y luego los N nombres que quedaron en el vector (para esa carrera).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

struct Par {
	char nombre[50];
	int pos;
};

bool operator<(const Par &A, const Par &B) {return A.pos < B.pos;}

string random_string(){
	string palabra(5, ' ');
	for(char &letra: palabra)
		letra = 'a'+rand()%26;
	return palabra;
}

void Ver_datos(string Oracion,int Cant_corredores, vector<Par> V){
	cout<<Oracion;
	size_t Carrera = 0;
	for(size_t i=0; i<V.size(); ++i){
		if(i == Carrera*Cant_corredores){
			cout<<"Carrera "<<Carrera+1<<endl;
			Carrera++;
		}
		cout<<V[i].pos<<"\t"<<V[i].nombre<<endl;
	}
}
	
void Mejores_N(string nombre_binario,string nombre_texto, int N){
	///a:
	ifstream f(nombre_binario, ios::binary|ios::ate);
	size_t Cantidad = f.tellg()/sizeof(Par);
	f.seekg(0);
	vector<Par> v;
	Par A;
	for (size_t i=0; i<Cantidad; ++i){
		f.read(reinterpret_cast<char*>(&A), sizeof(A));
		v.push_back(A);
	}
	f.close();
	///b:
	int Carreras = v.size()/20;
	auto it = v.begin();
	for(int i=0; i<Carreras; i++){ 
		sort(it, it+20);
		advance(it,20);
	}	
	/*for(int i=0;i<carreras;++i)
		sort(v.begin()+(i*20),v.begin()+(i*20)+20);*/
	///c:
	Ver_datos("\t\tDatos ordenados\n",20, v);
	for(int i=0; i<Carreras; ++i)
		v.erase(v.begin()+N+(i*N),v.begin()+20+(i*N));
	
	stringstream ss;
	ss<<"\t\tLos "<<N<<" primeros de cada carrera\n";
	Ver_datos(ss.str(),N, v);
	
	ofstream archi(nombre_texto, ios::trunc);
	size_t carrera = 0;
	for(size_t i=0; i<v.size(); ++i){
		if(i == carrera*N){
			archi<<"Carrera #"<<i<<":\n";
			carrera++;
		}
		archi<<v[i].nombre<<"  \n";
	}
	archi.close();
}
int main() {
	int Cantidad_registros = 40;
	int Competidores_por_carrera = 20;
	//Crear vector de Par con 40 datos de aleatorios 
	srand(time(0));
	vector<Par> V;
	for (int i=0; i<Cantidad_registros; ++i) {
		Par A;
		A.pos = i%Competidores_por_carrera + 1;
		string Nombre = random_string();
		strcpy(A.nombre, Nombre.c_str());
		V.push_back(A);
	}
	int Cantidad_Carreras = V.size()/Competidores_por_carrera;
	for (int i=0; i < Cantidad_Carreras; ++i)
		random_shuffle(V.begin()+(i*Competidores_por_carrera), V.begin()+(i*Competidores_por_carrera)+Competidores_por_carrera);   //desordeno
	Ver_datos("\tPosiciones\n", Competidores_por_carrera, V);
	
	//Volcar el vector de Par en binario
	string nombre_binario = "Resultados.dat";
	ofstream f(nombre_binario, ios::binary|ios::trunc);
	for(Par A: V)
		f.write(reinterpret_cast<char*>(&A), sizeof(A));
	f.close();
	
	//Generar txt con los N (5) mejores de cada carrera
	string nombre_texto = "Salida.txt";
	Mejores_N(nombre_binario, nombre_texto, 5);
	
	return 0;
}
