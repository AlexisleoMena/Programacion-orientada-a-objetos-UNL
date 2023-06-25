/*
Ejercicio 2 (35 pts)
a) Defina una clase Carrera que reciba en su constructor el nombre de un evento deportivo y la fecha del mismo. La clase debe
tener métodos para consultar estos datos y para gestionar una lista de participantes (nombre de cada uno).
b) Implemente, reutilizando la clase Carrera las clases Formula1 y MotoGP para representar carreras de estas dos categorías.
Estas clases deben tener un método CalcularPuntos que reciba el nombre de un participante, la posición en la que finalizó la
carrera, y un booleano para indicar si fue el autor de la vuelta más rápida. El método debe validar si el nombre es correcto (está
entre los inscriptos) y si lo es retornar la cantidad de puntos que obtuvo (si no es correcto, debe retornar -1).
- En la Fórmula 1, los 10 primeros reciben 25, 18, 15, 12, 10, 8, 6, 4, 2 y 1 puntos respectivamente. Pero además, si uno de los
10 primeros logra la vuelta rápida, suma un punto adicional.
- En Moto GP, los 15 primeros suman puntos según la siguiente escala: 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 (aquí no hay
bonificación alguna para quien logre la vuelta rápida).
c) Escriba una función “testCalcularPuntos" para probar el método CalcularPuntos. La función debe poder recibir cualquier tipo de
Carrera, y un vector con los nombres de los pilotos en el orden en que arribaron a meta. Debe mostrar el puntaje resultante de
cada uno (o un mensaje alusivo si un nombre no es correcto).
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct participante{
	string nombre;
	int puntaje=0;
};

class Carrera{
	string m_evento;
	string m_fecha;
	vector<string> V;
public:
	Carrera(string evento, string fecha, vector<string> &lista): m_evento(evento), m_fecha(fecha), V(lista){}
	string get_evento(){ return m_evento;}
	string get_fecha(){ return m_fecha;}
	string get_participante(int i){ return V[i];}
	int get_cantidad(){ return V.size();}
	virtual float CalcularPuntos(string, unsigned, bool) = 0;
};

class Formula1: public Carrera{
	vector<int> puntaje = {25,18,15,12,10,8,6,4,2,1};
public:
	Formula1(string evento, string fecha, vector<string> &lista): Carrera(evento,fecha,lista){}
	float CalcularPuntos(string nombre, unsigned pos, bool mejor_vuelta) override{
		int puntos_obtenidos = 0;
		for(int i=0; i<get_cantidad(); ++i){
			if(nombre == Carrera::get_participante(i)){
				if(puntaje.size()>pos){
					puntos_obtenidos += puntaje[pos]; 
					if(mejor_vuelta == 1)
						puntos_obtenidos++;
				}
				return puntos_obtenidos;
			}
		}
		return -1;
	}
	~Formula1(){}
};

class MotoGP: public Carrera{
	vector<int> puntaje = {25,20,16,13,11,10,9,8,7,6,5,4,3,2,1};
public:
	MotoGP(string evento, string fecha, vector<string> &lista): Carrera(evento,fecha,lista){}
	float CalcularPuntos(string nombre, unsigned pos,bool is=true) override{
		int puntos_obtenidos = 0;
		for(int i=0; i<get_cantidad(); ++i){
			if(nombre == Carrera::get_participante(i)){
				if(puntaje.size()>pos)
					puntos_obtenidos += puntaje[pos]; 
				return puntos_obtenidos;
			}
		}
		return -1;
	}
	~MotoGP(){}
};

void testCalcularPuntos(Carrera &A, const vector<string> &V){
	for(size_t i=0; i<V.size(); ++i){
		bool esta = false;
		for(int j=0; j<A.get_cantidad(); ++j){
			if(V[i] == A.get_participante(j)){
				esta = true;
				break;
			}
		}
		if(esta){
			cout<<V[i]<<": "
				<<A.CalcularPuntos(V[i],i,true)<<" pts"<<endl;
		}else{
			cout<<V[i]<<" NANANAN"<<endl;
		}
	}
}

int main() {
	vector<string> V = {"alexis","juan","oscar","kevin","carlos","leon"};
	Formula1 *A = new Formula1("MonteCarlo","2/10/2001",V);
	cout<<"Puntaje de oscar: "<<A -> CalcularPuntos("oscar",4,false)<<endl;
	
	
	vector<string> W= {"juan","kevin","alexis","leon","uriel","carlos"};
	testCalcularPuntos(*A,W);
	
	return 0;
}

