/*
Ejercicio 1 (35pts) Se dispone de un archivo binario "Pacientes.dat". 
El archivo fue creado por un programa C++ usando la expresion:
	archi.write(reinterpret_cast<char*>(&x),sizeof(x)); 
donde x es de tipo Ficha, siendo Ficha un struct que contiene los datos de cada paciente:
	DNI, nombre, apellido, direccion, telefono, obra social. 
Proponga una posible definicion del struct Ficha e implemente una funcion verificarDatos(...) que reciba como parametros el DNI de un paciente, un nombre y un apellido. 
La funcion debe buscarlo en el archivo (por su DNI) y verificar si el nombre y el apellido coinciden. 
Si encuentra al paciente en el archivo y los datos no coinciden, debe corregirlos (modificar nombre y apellido). 
Ademas debe retornar un entero con su posicion en la lista de pacientes (si es el 1ro de la lista, el 2do, 3ro, etc). Si el dni no estaba en la lista, debe retornar -1. 
Para implementar la funcion, no debe usar ningun contenedor (list, vector, etc) ni arreglo en memoria para cargar todos los datos, 
sino que debe operar directamente sobre el archivo.
*/

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Ficha{
	int Dni;
	char Nombre[64];
	char Apellido[64];
	char Direccion[64];
	int Telefono;
	char Obra_social;
};

int Verificar_Datos(string Nombre_archivo, int DNI, string NOMBRE, string APELLIDO){
	fstream f(Nombre_archivo, ios::binary|ios::in|ios::out|ios::ate);
	if(!f.is_open()){
		cout<<"Archivo no encontrado!!\n";
		exit(1);
	}
	int Cantidad_registros = f.tellg()/sizeof(Ficha);
	f.seekg(0);
	int Retorno = -1;
	for(int i=0; i<Cantidad_registros; ++i){
		Ficha A;
		f.read(reinterpret_cast<char*>(&A), sizeof(A));
		if(A.Dni == DNI){
			Retorno = i;
			if( strcmp(A.Nombre,NOMBRE.c_str()) or strcmp(A.Apellido, APELLIDO.c_str()) ){
				strcpy(A.Nombre, NOMBRE.c_str());
				strcpy(A.Apellido, APELLIDO.c_str());
				f.seekp(i*sizeof(Ficha));
				f.write(reinterpret_cast<char*>(&A), sizeof(A));
			}
			break; //Salir del for despues de encontrar la primer coincidencia
		}
	}
	return Retorno;
}

int main() {
	/*
	string Nombre_archivo = "Pacientes.dat";
	
	ofstream f(Nombre_archivo,ios::binary|ios::trunc);
	
	Ficha A;
	A.Dni = 23456789;
	strcpy(A.Nombre, "Federico");
	strcpy(A.Apellido, "Miranda");
	strcpy(A.Direccion, "Fedemiranda10@gmail.com");
	A.Telefono = 2222;
	A.Obra_social = 'S';
	f.write(reinterpret_cast<char*>(&A), sizeof(A));
	
	Ficha B;
	B.Dni = 12345678;
	strcpy(B.Nombre, "Juan");
	strcpy(B.Apellido, "Mena");
	strcpy(B.Direccion, "alexismena2690@gmail.com");
	B.Telefono = 1111;
	B.Obra_social = 'N';
	f.write(reinterpret_cast<char*>(&B), sizeof(B));
	
	f.close();
	
	int pos = Verificar_Datos(Nombre_archivo,12345678,"Alexis"s,"Mena"s);
	if(pos != -1){
		cout<<"Datos renombrados!\n";
		ifstream f(Nombre_archivo, ios::binary);
		f.seekg(1*sizeof(Ficha));
		Ficha A;
		f.read(reinterpret_cast<char*>(&A), sizeof(A));
		cout<<A.Nombre<<" "<<A.Apellido<<" "<<A.Direccion;
	}else{
		cout<<"DNI no encontrado!\n";
	}
	*/
	return 0;
}

