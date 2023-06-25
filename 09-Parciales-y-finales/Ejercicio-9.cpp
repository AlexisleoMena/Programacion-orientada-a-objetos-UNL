/*
Ejercicio 3 (35 pts)
En el diseño O. Objetos para un caso, se ha decidido plantear las siguientes dos clases:

-- Clase Alumno
Atributos:
	Nombre, dni, nota1, nota, nota 3, promedio, condición (‘P’,’R’o ‘L’)
Métodos:
	constructor o constructores
	calcular condición (calcula promedio y condición y devuelve esos 2 atributos).
	ver_datos_alumno (un solo método para devolver nombre, dni)

-- Clase Materia.
Atributos:
	nombre materia
	grupo de alumnos que la cursan (son 80, cada alumno tiene nombre, dni, nota1, nota2, nota 3, promedio, condición)
	nombre profesor
Métodos:
	constructor o constructores
	condiciones (calcula cantidades de regulares, libres y promocionados)
	buscar condición y promedio de un alumno (un solo método; parámetro: dni)
	cantidades (un solo método que calcule y devuelva cantidad de promocionados, cantidad libres, cantidad regulares )

Considerando que las condiciones posibles en la materia son: Promocionado si promedio>=60, Libre si promedio<40, Regular en
otro caso.
a) Establezca una relación de clases entre Alumno y Materia. Codifique las 2 clases con la sintaxis de C++.
b) Escriba un programa C++ cliente de dichas clases que lea los datos necesarios para inicializar una instancia de Materia e
informe las condiciones de los alumnos.
c) Además, el programa debe ingresar un dni y mostrar los datos del alumno, su promedio y condición en la materia.

*/
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

class Alumno{
	string m_nombre;
	int m_dni, m_nota1,m_nota2,m_nota3;
	float m_promedio;
	char m_condicion;
public:
	Alumno(){}
	Alumno(string nombre, int dni, int nota1, int nota2, int nota3): m_nombre(nombre), m_dni(dni), m_nota1(nota1),m_nota2(nota2), m_nota3(nota3){
		m_promedio = (m_nota1+m_nota2+m_nota3)/3;
		if(m_promedio>=60){
			m_condicion = 'P';
		}else if(m_promedio<40){
			m_condicion = 'L';
		}else{
			m_condicion = 'R';
		}
	}
	int get_dni(){ return m_dni;}
	float get_promedio(){ return m_promedio;}
	char get_condicion(){ return m_condicion;}
//	tuple<string,int> get_datos_alumno(){ return make_tuple(m_nombre, m_dni);}
//	tuple<float,char> calcular_condicion(){	return make_tuple(m_promedio, m_condicion);}

	~Alumno(){}
};

class Materia{
	string m_nombre_materia;
	vector<Alumno> &V;
	string m_nombre_profesor;
	vector<int> C = {0,0,0};
public:
	Materia(string materia, vector<Alumno> &lista, string profesor): m_nombre_materia(materia), V(lista), m_nombre_profesor(profesor){}
	void Cargar_condiciones(){
		C[0] = count_if(V.begin(), V.end(), [] (Alumno &A) { return A.get_condicion() == 'P';});
		C[1] = count_if(V.begin(), V.end(), [] (Alumno &A) { return A.get_condicion() == 'R';});
		C[2] = count_if(V.begin(), V.end(), [] (Alumno &A) { return A.get_condicion() == 'L';});
	}
	
	tuple<float, char> Buscar_prom_y_cond(int DNI){
		auto pos = find_if(V.begin(), V.end(), [=] (Alumno &A) { return A.get_dni() == DNI;});
		if(pos != V.end()){
			return make_tuple(V[pos-V.begin()].get_promedio(), V[pos-V.begin()].get_condicion());
		}else{
			return make_tuple(00,'X');
		}
		
	}
	void Devolver_condiciones(){
		cout<<"\nPROMOVIDOS: "<<C[0];
		cout<<"\nREGULARES: "<<C[1];
		cout<<"\nLIBRES: "<<C[2];
	}
};

int main() {
	vector<Alumno> V = {{"Alexis",1111,70,70,70},{"Juan",2222,50,50,50},{"Carlos",3333,10,10,10},{"Kevin",4444,50,50,50}};
	Materia M("Matematicas",V,"Gabriel");
	M.Cargar_condiciones();
	M.Devolver_condiciones();
	
	float promedio=0; char condicion='X';
	tie(promedio, condicion) = M.Buscar_prom_y_cond(2222);
	cout<<"\nPROMEDIO: "<<promedio<<"\nCONDICION: "<<condicion;
	
	return 0;
}

