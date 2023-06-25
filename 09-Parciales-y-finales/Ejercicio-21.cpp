/*
Ejercicio 3 (35 pts) - Un archivo "estudio.txt" contiene en texto los resultados de un estudio sobre una nueva vacuna. Por cada participante 
hay primero un entero indicando si se enfermo (1) o no (0), luego un espacio y finalmente un codigo de individuo formado por 3 letras y 3 numeros. Primero estan todos los datos de los participantes que conformaron el grupo de control (que recibieron el placebo), luego un 
registro especial para separar que tiene '2' en el entero y "------" como codigo, y luego los datos de los participantes restantes
(quienes recibieron la verdadera vacuna). Escriba una funcion analizarResultados(...) que a) abra el archivo y cargue todos los datos en
un unico vector de structs. Luego, usando funciones de la stl, b) ordene por codigo el 2do grupo, c) en cada grupo calcule el porcentaje de
infectados sobre el total, y d) genere un archivo de texto "reporte.txt" que contenga los siguientes resultados: cantidad de individuos total 
en cada grupo, porcentaje de infectados en cada grupo, y finalmente una lista de los codigos de las personas que se infectaron a pesar de que
recibieron la vacuna (que debera estar ordenado por codigo segun el item b).
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Participante {
	int Estado; 
	string Codigo;
};

bool Esta_enfermo(Participante A) {return A.Estado == 1;}

bool Comparar_por_Codigo(Participante A, Participante B) {return A.Codigo < B.Codigo;}

void Analizar_Resultados(string Nombre_archivo){
	///a:
	ifstream f(Nombre_archivo,ios::in|ios::out);
	vector<Participante> v;
	Participante A;
	while(f>>A.Estado>>A.Codigo)
		v.push_back(A);
	///b:
	auto it_corte = find_if(v.begin(), v.end(), [] (const Participante &A){ return A.Estado == 2;});
	sort(it_corte+1, v.end(), Comparar_por_Codigo);
	///c:
	int Cant_placebos = (it_corte-v.begin());
	int Porc_placebos = (count_if(v.begin(),it_corte,Esta_enfermo)*100) / Cant_placebos;
	int Cant_vacunados = (v.end()-(it_corte+1));
	int Porc_vacunados = (count_if(it_corte+1,v.end(),Esta_enfermo)*100) / Cant_vacunados;
	///d:
	ofstream f2("informe.txt",ios::trunc);
	f2<<"Grupo 1\n Total: "<<Cant_placebos<<"\n % infectados: "<<Porc_placebos<<endl;
	f2<<"Grupo 2\n Total: "<<Cant_vacunados<<"\n % infectados: "<<Porc_vacunados<<endl;
	f2<<"Infectados a pesar de recibir dosis: "<<endl;
	for(auto it = it_corte+1; it!=v.end(); ++it)
		if (it -> Estado == 1) 
			f2<<it -> Codigo<<endl;
}
int main() {
	string Nombre_archi = "Ejercicio3.txt";
	ofstream archi_out(Nombre_archi);
	archi_out<<"0 AAAA\n1 AAAC\n1 AAAD\n0 AAAB\n2 ----\n0 EEEE\n1 BBBB\n1 DDDD\n0 CCCC\n";
	archi_out.close();
	
	Analizar_Resultados(Nombre_archi);
	return 0;
}
