/*
Ejercicio 3
a) En la clase Alumno: ya están completos los datos o atributos; proponga un constructor para iniciar sus datos: nombre,
DNI y nota_final; un método para determinar la condición: 'R' o 'L' ('R' es Regular si nota_final>=4, 'L' es Libre si
nota_final<4) y otros métodos que considere necesarios o adecuados para consultar los datos de la clase.
b) Proponga una clase Materia, que reutilice la clase Alumno mediante la relación que considere más adecuada. La clase
Materia debe permitir definir el nombre de la materia, el nombre del profesor, y registrar varios alumnos. Proponga un
constructor, y métodos para obtener la cantidad de regulares y de libres; y otros métodos que crea necesarios.
Solo proponga las clases y codifique sus métodos (no hacer programa cliente).
class Alumno {
 string nombre;
 int DNI, nota_final;
 . . .
 public:
 . . .
};
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Alumno {
	string m_nombre;
	int m_dni, m_nota_final;
public:
	Alumno(){}
	Alumno(string nombre, int dni, int nota): m_nombre(nombre), m_dni(dni), m_nota_final(nota){}
	string get_nombre() const { return m_nombre;}
	int get_dni() const { return m_dni;}
	int get_nota() const { return m_nota_final;}
	char condicion(){ return (m_nota_final<4)? 'L':'R';}
	~Alumno(){}
};

class Materia: public Alumno{
	string m_nombre_materia, m_nombre_profe;
	vector<Alumno> &m_lista;
public:
	Materia(string nombre_materia, string nombre_profesor, vector <Alumno> &lista):
		m_nombre_materia(nombre_materia), m_nombre_profe(nombre_profesor), m_lista(lista){} 
	int cantidad_regulares(){
		return count_if(m_lista.begin(), m_lista.end(), [] (Alumno x){ return x.condicion() == 'R';});
	}
	int cantidad_libres(){
		return (m_lista.size() - Materia::cantidad_regulares());
	}
	~Materia(){}
};

int main() {
	vector<Alumno> V(5);
	V[0] = {"Alexis", 39246499, 6};
	V[1] = {"Kevin", 19346429, 5};
	V[2] = {"Juan", 49241429, 3};
	V[3] = {"Jorge", 29341429, 4};
	V[4] = {"Oscar", 19241429, 2};
	Materia Mates("Matematica","julio",	V);
	cout<<"REGULARES: "<<Mates.cantidad_regulares();
	cout<<"\nLIBRES: "<<Mates.cantidad_libres();
	return 0;
}

