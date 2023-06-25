/*
Ejercicio 2
En una aplicación que gestiona los datos de un conjunto de estudiantes, hay una función para obtener los n mejores
promedios para otorgarles un cierta beca:
void obtenerBeneficiados(int n, ProgressIndicator &p) {
	p.comenzar(5);
	vector<Alumnos> v = cargarDatos("alumnos.dat");
	p.paso();
	for(Alumno &a : v)
	filtrarInsuficientes(a.notas);
	p.paso();
	for(Alumno &a : v)
	a.prom = calcularPromedio(a.notas);
	p.paso();
	ordenarVector(v,comparaPorPromedio);
	p.paso();
	v.resize( n );
	guardarDatos("becarios.dat");
	p.finalizar();
}
La función recibe la cantidad de becarios que debe obtener, y un objeto p que se encargará de informarle al usuario el
progreso de la aplicación. Antes de comenzar a procesar los datos, con el método comenzar(5) se le indica a p que comienza
el procesamiento, y cuantos pasos van a ser (argumento del método, en este ej 5). Luego, cada vez que la aplicación
completa un paso, se invoca al método "paso()". Cuando el proceso se completa y todos los pasos están listos, se invoca al
método "finalizar()".
Diseñe dos clases: TextualProgress y PorcentualProgress, para usar como 2do argumento de la función (sin modificarla):
* La primera, en los método comenzar y paso, deberá mostrar el mensaje "Ejecutando paso I de N" (reemplazando I por
el número de paso en que va, y N por el total); y el método finalizar, el mensaje "Ejecución finalizada.".
* La segunda, en los método comenzar y paso, deberá mostrar el mensaje "Progreso: X%" (reemplazando X por el
porcentaje de avance actual según el paso en que está y la cantidad total); y el método finalizar, el mensaje "Proceso
completado con éxito.".
Escriba un programa cliente que permita al usuario elegir entre ambas opciones e invoque a la función obtenerBeneficiados
para encontrar los 10 mejores promedios. Responda, ¿exactamente qué problema/error tendría al compilar o ejecutar su
programa si la función no recibiera el argumento p por referencia?
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Carrera{
	string m_nombre_evento;
	string m_fecha;
//protected:
	vector<string> &V;
public:
	Carrera(string nombre, string fecha, vector<string> &lista): m_nombre_evento(nombre), m_fecha(fecha), V(lista) {}
	string get_nombre_evento()const { return m_nombre_evento;}
	string get_fecha()const { return m_fecha;}
	string get_participante(int i)const { return V[i];}
	int get_size_lista()const { return V.size();}
	virtual void CalcularPuntaje(string, int, bool) = 0;
	virtual ~Carrera(){}
};

class Formula1: public Carrera{
	vector<int> Puntajes = {25,18,15,12,10,8,6,4,2,1};
public:
	Formula1(string nombre, string fecha, vector<string> &lista): Carrera(nombre,fecha,lista) {}
	void CalcularPuntaje(string, int, bool) override;
	int get_size_puntajes(){ return Puntajes.size();}
	~Formula1(){}
};

class MotoGP: public Carrera{
	vector<int> Puntajes = {25,20,16,13,11,10,9,8,7,6,5,4,3,2,1};
public:
	MotoGP(string nombre, string fecha, vector<string> &lista): Carrera(nombre,fecha,lista) {}
	void CalcularPuntaje(string, int, bool) override;
	int get_size_puntajes(){ return Puntajes.size();}
	~MotoGP(){}
};

void testCalcularPuntos(Carrera &A, const vector<string> &Llegada){
	for(size_t i=0; i<Llegada.size(); ++i)
		A.CalcularPuntaje(Llegada[i],i,false);
}


int main() {
	vector<string> lista = {"Alexis","Jorge","Leon","Agustina","Jose","Sebastian","Kevin","Juan"};
	Carrera *A = new Formula1("MonteCarlo","02/10/1994",lista);
//	A -> CalcularPuntaje("Alexis",2,true);
	
	vector<string> Llegada = {"Jorge","Oscar","Agustina","Jose","Sebastian","Alexis","Juan"};
	testCalcularPuntos(*A,Llegada);
	
	delete A;
	return 0;
}


void Formula1 :: CalcularPuntaje(string nombre, int posicion, bool vuelta_rapida){
	bool esta = false;
	for(int j=0; j<get_size_lista(); ++j){
		if(nombre == get_participante(j)){
			esta = true;
			break;
		}
	}
	if(esta){
		int puntos = 0;
		if(posicion<get_size_puntajes())
			puntos = Puntajes[posicion];
		if(vuelta_rapida and posicion<10)
			puntos++;
		cout<<nombre<<": "<<puntos<<" pts"<<endl;
	}else{
		cout<<nombre<<" NANANAN"<<endl;
	}
}
void MotoGP :: CalcularPuntaje(string nombre, int posicion, bool vuelta_rapida){
	bool esta = false;
	for(int j=0; j<get_size_lista(); ++j){
		if(nombre == get_participante(j)){
			esta = true;
			break;
		}
	}
	if(esta){
		int puntos = 0;
		if(posicion<get_size_puntajes())
			puntos = Puntajes[posicion];
		cout<<nombre<<": "<<puntos<<" pts"<<endl;
	}else{
		cout<<nombre<<" NANANAN"<<endl;
	}
}
