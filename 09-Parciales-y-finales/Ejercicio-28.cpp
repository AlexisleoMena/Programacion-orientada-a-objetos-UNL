/*
Ejercicio 3 (30pts) 
Realice un programa que lea archivo de texto llamado "email.txt" que contiene una lista de correos y lo analice,
contando cuantas veces se repite cada dominio. Debe generar otro archivo de texto "estadisticas.txt", en el cual cada fila contenga el 
nombre de dominio y la cantidad de correos que utilizan dicho dominio; estas lineas deben estar ordenadas en forma descendente por cantidad. 
(Nota: el dominio es la la parte de la direccion de correo que se encuentra luego de la '@')
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Dominio{
	string dom;
	int rep;
};

bool operator == (Dominio a, Dominio b){ return a.dom == b.dom;}
//bool operator > (Dominio a, Dominio b){ return a.rep > b.rep;}

int main() {
	ofstream prueba("email.txt",ios::trunc);
	prueba<<"a@gmail.com\nb@gmail.com\nc@hotmail.com.ar\nd@yahoo.com.ar";
	prueba.close();
	
	ifstream f("email.txt");
	string mail;
	vector<Dominio> V;
	while(f>>mail){
		Dominio A;
		A.dom = mail.substr( mail.find('@')+1 );
		A.rep = 1;
		auto it = find(V.begin(), V.end(), A);
		if(it != V.end())
			++it->rep;
		else
			V.push_back(A);
	}
	f.close();
	//sort(V.begin(), V.end(), greater <>());
	sort(V.begin(), V.end(), [] (const Dominio &A, const Dominio &B){return A.rep>B.rep;});
	
	ofstream ofile("estadisticas.txt");
	for(Dominio &A : V)
		ofile<<A.dom<<"\t"<<A.rep<<endl;
	
	return 0;
}
