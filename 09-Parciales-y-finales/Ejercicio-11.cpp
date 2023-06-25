/*
Ejercicio 2 (35 pts)
a) Defina una clase Asignatura que reciba en su constructor el nombre de una materia y el número de cuatrimestre al que
pertenece. La clase debe tener métodos para consultar estos datos y para gestionar una lista de "unidades" (strings).
b) Implemente, reutilizando la clase Asignatura, las clases FuPro y CompGraf para representar las materias “Fundamentos de
Programación” y “Computación Gráfica” respectivamente. Estas clases deben tener un método CalcularCondicion que reciba un
vector de elementos de tipo struct Evaluacion { string tipo; int nota; } con los resultados de un alumno. El método debe verificar
que los tipos de evaluaciones sean los correctos (si no lo son, deberá retornar "error"), y calcular su condición final en base a sus
notas la condición final del alumno.
- Para FuPro, las evaluaciones deben ser de tipos "parcial1" y "parcial2"; y la condición final será "promocionado" si el promedio
llega a 70 y la nota mínima no es menor de 60, "regular" si la nota mínima no baja de 40, o "libre" en caso contrario.
- Para CompGraf, las evaluaciones deben ser de tipos "tp1" y "tp2", "tpFinal", y "parcial". La condición final será "promocionado"
si todos los tps están aprobados (nota 60 o superior) y el parcial tiene 65 o más; "regular" si los tps están aprobados pero el
parcial no, o "libre" si algún tp está desaprobado.
c) Escriba una función “testCalcularCondicion” para probar el método CalcularCondicion. La función debe poder recibir cualquier
Materia, permitir al usuario ingresar un vector de Evaluaciones y mostrar la condición resultante.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Evaluacion{
	string tipo;
	int nota;
};

class Materia{
	string m_nombre;
	int m_cuatrimestre;
	vector<string> m_unidades;
public:
	Materia(string materia, int cuatrimestre): m_nombre(materia), m_cuatrimestre(cuatrimestre){	}
	string get_nombre() const{ return m_nombre;}
	int get_cuatrimestre() const{ return m_cuatrimestre;}
	void set_unidad(string titulo){ m_unidades.push_back(titulo);}
	string get_unidad(int i){ return m_unidades[i];}
	int get_size_unidades(){ return m_unidades.size();}
	virtual string CalcularCondicion(const vector<Evaluacion> &) const = 0;
	virtual ~Materia(){}
};

class Fupro: public Materia{
public:
	Fupro(int cuatrimestres): Materia("Fundamentos de programacion",cuatrimestres){	}
	string CalcularCondicion(const vector<Evaluacion> &V) const {
		if(V.size() == 2 and V[0].tipo == "parcial1" and V[1].tipo == "parcial2"){
			if((V[0].nota+V[1].nota)/2.0 >= 70 and V[0].nota>=60 and V[1].nota>=60){
				return "Promocionado";
			}else{
				if(V[0].nota>=40 and V[1].nota>=40){
					return "Regular";
				}else{
					return "Libre";
				}
			}
		}else{
			return "Error";
		}
	}
	~Fupro(){}
};

class CompGraf: public Materia{
public:
	CompGraf(int cuatrimestres): Materia("Computacion grafica",cuatrimestres){	}
	string CalcularCondicion(const vector<Evaluacion> &V) const {
		if( V.size()==4 and V[0].tipo=="tp1" and  V[1].tipo=="tp2" and V[2].tipo=="tpFinal" and V[3].tipo=="parcial" ){
			if(V[0].nota>=60 and V[1].nota>=60 and V[2].nota>=60){
				if(V[3].nota>=65){
					return "Promocionado";
				}else{
					return "Regular";
				}
			}else{
				return "Libre";
			}
		}else{
			return "error";
		}
	}
	~CompGraf(){}
};

void testCalcularCondicion(Materia &A){
	vector<Evaluacion> V;
	Evaluacion e;
	cout<<"\nTipo (salir con exit): ";
	cin>>e.tipo;
	while(e.tipo != "exit"){
		cout<<"Nota: ";
		cin>>e.nota;
		V.push_back(e);
		cout<<"Tipo(salir con exit): ";
		cin>>e.tipo;
	}
	cout<<"Condicion: "<<A.CalcularCondicion(V)<<endl;
}

int main() {
	vector<Evaluacion> F = {{"parcial1", 70},{"parcial2", 70}};
	vector<Evaluacion> CG = {{"tp1", 60},{"tp2", 60},{"tpFinal",60},{"parcial",50}};
	
	Materia *Alexis[2];
	Alexis[0] = new Fupro(1);
	Alexis[1] = new CompGraf(1);
	
	cout<<"Condicion de Alexis en el 1er cuatri de Fundamentos: "<<Alexis[0] -> CalcularCondicion(F)<<endl;
	cout<<"Condicion de Alexis en el 1er cuatri de Computacion grafica: "<<Alexis[1] -> CalcularCondicion(CG)<<endl;
	
	delete Alexis[0];
	delete Alexis[1];
	
	Materia *Juan = new Fupro(2);
	cout<<"\nCalcular condicion Juan en el 2do cuatri de Fupro (parcial1,parcial2): ";
	testCalcularCondicion(*Juan);
	
	Materia *Oscar = new CompGraf(2);
	cout<<"\nCalcular condicion Oscar en el 2do cuatri de Computacion grafica (tp1,tp2,tpFinal,parcial): ";
	testCalcularCondicion(*Oscar);
	
	delete Juan;
	delete Oscar;
	
	return 0;
}

