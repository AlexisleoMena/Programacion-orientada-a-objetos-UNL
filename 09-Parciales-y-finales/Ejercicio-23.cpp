/*
Ejercicio 2 (35 pts) Escriba una clase que posea: 
a) un constructor que reciba el nombre de un archivo de texto y almacene los datos del
archivo en un vector de la STL. La estructura de los elementos del vector debe ser la siguiente: struct Persona{int fecha; string apenom;);
Cada linea del archivo contiene datos de personas, una por linea con el formato: "aaaammdd Apellidos, Nombres". El/los apellidos estan
separados de el/los nombres por una coma, por ejemplo: Royaltes, Horacio Cesar. aaaammdd es la fecha de nacimiento (año, mes y dia todo pegado) 
Implemente: 
b) un metodo cambiarFormato() que modifique las cadenas del vector de manera que queden con el siguiente formato: "Nombres Apellidos" (por ejemplo: Horacio Cesar Royaltes); 
c) un metodo ordenar que ordene el vector segun la fecha de nacimiento; y 
d) un metodo guardar() que no reciba ningun parametro y sobreescriba el archivo original con los nuevos datos almacenados en el vector.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Persona {
	int fecha;
	string apenom;
};

bool operator < (const Persona &A, const Persona &B) {return A.fecha < B.fecha;}

class ManejarPersonas {
	vector<Persona> v;
	string Nombre_archivo;
public:
	///a:
	ManejarPersonas(string nombre): Nombre_archivo(nombre) {
		ifstream f(Nombre_archivo);
		if (!f.is_open()) {
			cout << "!!!Archivo no encontrado!!!\n";
			exit(1);
		}
		Persona A;
		while(f >> A.fecha) {
			f.ignore();
			getline(f, A.apenom); 
			v.push_back(A);
		}
	};
	///b:
	void CambiarFormato(){
		for(Persona &A : v) { 
			size_t poscoma = A.apenom.find(',');
			A.apenom = A.apenom.substr(poscoma+2)+" "+A.apenom.substr(0,poscoma);   //+2 para saltear la ", "
		}
	}
	///c:
	void Ordenar(){
		sort(v.begin(),v.end());
	}
	///d:
	void Guardar(){
		ofstream archi(Nombre_archivo, ios::trunc);
		for(Persona &A: v)
			archi<<A.fecha<<" "<<A.apenom<<endl;
	}
};

int main() {
	string Nombre_archivo = "datos.txt";
	ofstream f(Nombre_archivo, ios::trunc);
	f<<"11102021 Mena, Alexis Leonardo\n12122012 Lopez, Juan Carlos\n09122012 Bernardi, Bruno Ezequiel\n09112012 Jurado, Lorenzo Julian\n";
	f.close();
	ManejarPersonas MP(Nombre_archivo);
	MP.CambiarFormato();
	MP.Ordenar();
	MP.Guardar();
	return 0;
}


