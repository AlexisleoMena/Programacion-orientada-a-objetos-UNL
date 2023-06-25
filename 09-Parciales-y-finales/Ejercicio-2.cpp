/*
Ejercicio 2
En una aplicación que gestiona los datos de un conjunto de estudiantes, hay una función para obtener los n mejores
promedios para otorgarles una cierta beca:
void obtenerBeneficiados(int n, LogSystem log) {
 log.registrarMensaje("Cargando archivo de datos");
 vector<Alumnos> v = cargarDatos("alumnos.dat");
 log.registrarMensaje("Filtrando Insuficientes");
 for(Alumno &a : v)
 filtrarInsuficientes(a.notas);
 log.registrarMensaje("Recalculando promedios");
 for(Alumno &a : v)
 a.prom = calcularPromedio(a.notas);
 log.registrarMensaje("Ordenando por promedio");
 ordenarVector(v,comparaPorPromedio);
 log.registrarMensaje("Guardando los "+to_string( n )+" mejores");
 v.resize( n );
 guardarDatos("becarios.dat");
 log.finalizar();
}
La función recibe la cantidad de becarios que debe obtener, y un objeto para "loggear" sus acciones (registrar qué acciones
realiza en cada paso mediante mensajes de texto).
Utilizando polimorfismo, diseñe dos clases: CoutLogger y VectorLogger, para usar como 2do argumento de la función
(sin modificarla):
* La primera debe escribir en pantalla los mensajes que recibe inmediatamente cuando los recibe (método
registrarMensaje(...)), y no hacer nada más al finalizar.
* La segunda debe guardar los mensajes en un vector de strings a medida que los recibe, y mostrarlos todos juntos al
finalizar (método finalizar()).
Escriba un programa cliente que permita al usuario elegir el mecanismo de logging e invoque a la función
obtenerBeneficiados para encontrar los 10 mejores promedios. Para que todo esto funcione correctamente, deberá hacer un
pequeño cambio en el prototipo de la función obtenerBeneficiados, ¿cuál? y ¿por qué?
*/

#include <iostream>
#include <vector>

using namespace std;

class LogSystem{
public:
	virtual void registrarMensaje(string) = 0; //metodos virtuales para que las clases hijas puedan implementarlos
	virtual void finalizar() const = 0;
	~LogSystem(){}
};

class CoutLogger : public LogSystem{
public:
	void registrarMensaje(string new_log) override { cout<<new_log<<endl;} 
	void finalizar() const override{}
};

class VectorLogger : public LogSystem{
	vector<string> logs;
public:
	void registrarMensaje(string nuevo_log){ logs.push_back(nuevo_log);}
	void finalizar() const override{
		for(string log: logs)
			cout<<log<<endl;
	}
};

///"LogSystem" es una clase abstracta no puede ser instanciada.
///"LogSystem &log" permite a las clases heredadas utilizar e implementar metodos de la clase padre.

void obtenerBeneficiados(int n, LogSystem &log) {
	log.registrarMensaje("Cargando archivo de datos");
//	vector<Alumnos> v = cargarDatos("alumnos.dat");
	log.registrarMensaje("Filtrando Insuficientes");
//	for(Alumno &a:v)
//		filtrarInsuficientes(a.notas);
	log.registrarMensaje("Recalculando promedios");
//	for(Alumno &a:v)
//		a.prom = calcularPromedio(a.notas);
	log.registrarMensaje("Ordenando por promedio");
//	ordenarVector(v,comparaPorPromedio);
	log.registrarMensaje("Guardando los "+to_string(n)+" mejores");
//	v.resize(n);
//	guardarDatos("becarios.dat");
	log.finalizar();
}

int main() {
	char elegir_logSystem;
	cout << "ELEGIR LOG SYSTEM: \n"
		<< "V. VectorLogger\n"
		<< "C. CoutLogger\n";
	cin >> elegir_logSystem;
	
	if (elegir_logSystem == 'V') {
		VectorLogger vec_log;
		obtenerBeneficiados(10, vec_log);
	} else if (elegir_logSystem == 'C') {
		CoutLogger cout_log;
		obtenerBeneficiados(10, cout_log);
	} else cout << "No se eligio una de las opciones." << endl;
	return 0;
}
