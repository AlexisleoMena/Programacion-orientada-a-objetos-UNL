/*
Ejercicio 2 (35pts)
a) Diseñe una clase para representar un viaje que guarde y permita consultar la siguiente información: ciudades de origen y
destino, medio de transporte (un string, por ej "avión”), y distancia (en kms).
b) Implemente 3 clases que representen viajes en tres medios de transportes específicos: en avión, en auto y en colectivo.
Cada una de estas clases debe permitir obtener el tiempo del viaje de la siguiente forma:
 - en auto: t = distancia/110 + .5*(distancia%110) // se viaja a 110km/h, con un descanso de 30m cada 2h
 - en avión: t = 2+distancia/900 // se viaja a 900km/h, pero hay que estar 2 horas antes en el aeropuerto
 - en colectivo: t = distancia/90 // se viaja a 90km/h, sin esperas antes ni paradas
c) Implemente una función que reciba un vector de viajes y retorne el tiempo total (la suma).
d) Escriba un programa cliente que genere un vector con 3 viajes: de Rosario a Paraná en auto (200km), de Paraná a Buenos
Aires en avión (400km), y de Buenos Aires a Rosario en colectivo (320km). El programa debe usar la función para obtener
y luego mostrar el tiempo total.
*/

#include <iostream>
#include <vector>

using namespace std;

class Medio{
public:
	virtual float get_tiempo(int)=0;
	virtual string get_medio()=0;
	virtual ~Medio(){}
};

class Viaje{
	string m_origen, m_destino;
	int m_distancia;
	Medio *m_ptr;
public:
	Viaje(string origen, string destino, int distancia, Medio *ptr): m_origen(origen), m_destino(destino), m_distancia(distancia), m_ptr(ptr){}
//	string get_origen()const{ return m_origen;}
//	string get_destino()const{ return m_destino;}
//	int get_distancia()const{ return m_distancia;}
	float TiempoDeViaje(){return m_ptr -> get_tiempo(m_distancia);}
	string MedioTransporte(){return m_ptr -> get_medio();}
};

class Auto: public Medio{
public:
	float get_tiempo(int d){return d/110.0+5*(d%110);}
	string get_medio(){return "Auto";}
};

class Avion: public Medio{
public:
	float get_tiempo(int d){return 2+d/900.0;}
	string get_medio(){return "Avion";}
};

class Colectivo: public Medio{
public:
	float get_tiempo(int d){return d/90.0;}
	string get_medio(){return "Colectivo";}
};

float TiempoTotal(vector<Viaje> &V){
	float Total=0;
	for(size_t i=0;i<V.size();i++) {
		cout<<"\nMedio de transporte: "<<V[i].MedioTransporte()<<"  : "<<V[i].TiempoDeViaje();
		Total += V[i].TiempoDeViaje();
	}
	return Total;
}

int main() {
	vector<Viaje> V;
	V.push_back(Viaje("Rosario","Parana",200,new Auto));
	V.push_back(Viaje("Parana","Buenos Aires",400,new Avion));
	V.push_back(Viaje("Buenos Aires","Rosario",320,new Colectivo));
	
	float tiempo=TiempoTotal(V);
	cout<<"\ntiempo total de viajes: "<<tiempo<<endl;
	
	return 0;
}

