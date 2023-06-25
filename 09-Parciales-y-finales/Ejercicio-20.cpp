/*
Ejercicio 2. (35 pts) La clase Curso, maneja un archivo binario ALUMNOS.DAT con los datos de un grupo de estudiantes. Los datos fueron 
almacenados empleando un struct cuyos miembros son: dni, nota1, nota2, nota3, apellido, nombres. Los registros se hallan almacenados ordenados
en forma creciente por DNI. Por error se han registrado algunos alumnos 2 veces por lo que sus datos se encuentran repetidos. Escriba la clase
Curso que 
a) en su constructor acceda al archivo y cargue los datos en un contenedor; 
b) a traves de un metodo elimine los registros  repetidos; y 
c) mediante otro metodo exporte todos los datos del archivo binario a un archivo de textos cuyo nombre recibe como parametro. 
Cada linea  debe tener el apellido del alumno y sus iniciales (Por ejemplo para "Juan Luis Perez" deberia ir "Perez J. L."), el  dni y su promedio.
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Estudiante {
	int dni, nota1, nota2, nota3;
	char apellido[64], nombres[64];
};

bool operator == (Estudiante A, Estudiante B) { return B.dni == A.dni;}

class Curso {
	vector<Estudiante> Alumnos;
public:
	Curso(string nom_archi) {
		ifstream f(nom_archi,ios::binary|ios::ate);
		Alumnos.resize(f.tellg()/sizeof(Estudiante));
		f.seekg(0);
		for(Estudiante &A : Alumnos)
			f.read(reinterpret_cast<char*>(&A),sizeof(A));
	}
	void EliminarRepetidos() {
		auto it = unique(Alumnos.begin(),Alumnos.end());
		Alumnos.erase(it,Alumnos.end());
	}
	void Guardar(string nom_archi) {
		ofstream f(nom_archi, ios::trunc);
		for(Estudiante A : Alumnos) {
			float PROMEDIO = (A.nota1+A.nota2+A.nota3)/3.0;
			string NOMBRES = A.nombres;
			string INICIALES;
			for(size_t i=0;i<NOMBRES.size();++i) { 
				if (NOMBRES[i]>='A' and NOMBRES[i]<='Z') {
					INICIALES += NOMBRES[i];
					INICIALES += ". ";
				}
			}
			f << A.apellido << " " << INICIALES << A.dni << " " << PROMEDIO << endl;
		}
	}
};

int main() {
//	string Nombre_binario = "Ejercicio2.dat";
//	string Nombre_texto = "Ejercicio2.txt";
//	ofstream archi_out(Nombre_binario,ios::binary|ios::trunc);
//	for(int i=1; i<=3; ++i){
//		Estudiante A;
//		string Aux;
//		cout<<"\nNombres: "; getline(cin,Aux);
//		strcpy(A.nombres,Aux.c_str());
//		cout<<"Apellido: "; cin>>A.apellido;
//		cout<<"DNI: "; cin>>A.dni;
//		cout<<"Nota 1: "; cin>>A.nota1;
//		cout<<"Nota 2: "; cin>>A.nota2;
//		cout<<"Nota 3: "; cin>>A.nota3;
//		archi_out.write(reinterpret_cast<char*>(&A), sizeof(A));
//		cin.ignore();
//	}
//	archi_out.close();
//	Curso A(Nombre_binario);
//	A.EliminarRepetidos();
//	A.Guardar(Nombre_texto);
	return 0;
}
