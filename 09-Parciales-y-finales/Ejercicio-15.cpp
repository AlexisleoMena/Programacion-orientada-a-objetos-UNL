/*
Ejercicio 2 (35 pts)
a) Diseñe clase Carrera que permita almacenar y consultar el nombre de la carrera, el promedio
histórico de los egresados de la misma (es un solo número real), y la lista de materias del plan.
Agregue además un método que reciba un nombre de materia y retorne en qué posición del plan
de carrera se encuentra (si es la 1ra materia, la 2da, o cual).
b) A través de alguna relación de clases utilice la clase Carrera para diseñar las clases
IngMecanica y Arquitectura. Estas clases deberán tener un método para calcular el promedio de
un alumno que la haya completado, a partir de un vector con los datos de todos los sus exámenes
(vector de struct Examen { int fecha; string materia; int nota; } ).
- En la carrera de Ing. Mecánica, que tiene 42 materias, para calcular el promedio no se toman en
cuenta los insuficientes (nota menor a 6), y se deben considerar las últimas 12 materias del plan
con peso doble (en el promedio, las notas de estas materias se deben sumar dos veces, y luego
se debe dividir por 54 en lugar de 42).
- En Arquitectura se calcula el promedio habitual (sumar una vez cada nota y dividir por la
cantidad real), considerando todos los exámenes (incluyendo los insuficientes).
Nota: el vector de exámenes que se recibe está ordenado por la fecha en que el alumno rindió, y
no por el orden de las materias en el plan.
c) Un alumno puede acceder a una beca de posgrado si su promedio supera al promedio histórico
y tiene menos de 3 insuficientes. Escriba una función beca_posgrado que reciba una carrera
(debe poder recibir cualquiera de las dos) y un vector de exámenes correspondiente a un alumno,
y retorne un booleano indicando si el alumno está en condiciones de acceder a la beca.

*/
#include <iostream>
#include <vector>
using namespace std;

struct Examen {
	int fecha;
	string materia;
	int nota;
};

class Carrera {
	string nombre;
	float promedioHistorico;
	vector<string> materias;

public:
	Carrera(string nombre, float promedioHistorico, vector<string> materias)
		: nombre(nombre), promedioHistorico(promedioHistorico), materias(materias) {}

	string getNombre() const { return nombre; }

	float getPromedioHistorico() const { return promedioHistorico; }

	vector<string> getMaterias() const { return materias; }

	int obtenerPosicionMateria(string nombreMateria) const
	{
		for (size_t i = 0; i < materias.size(); i++)
		{
			if (materias[i] == nombreMateria)
			{
				return i + 1;
			}
		}
		return -1; // Materia no encontrada
	}
};

class IngMecanica : public Carrera {
public:
	IngMecanica()
		: Carrera("Ing. Mecánica", 0.0,
			{"Materia1", "Materia2", "Materia3", "Materia4", "Materia5", "Materia6", "Materia7", "Materia8",
				"Materia9", "Materia10", "Materia11", "Materia12", "Materia13", "Materia14", "Materia15",
				"Materia16", "Materia17", "Materia18", "Materia19", "Materia20", "Materia21", "Materia22",
				"Materia23", "Materia24", "Materia25", "Materia26", "Materia27", "Materia28", "Materia29",
				"Materia30", "Materia31", "Materia32", "Materia33", "Materia34", "Materia35", "Materia36",
				"Materia37", "Materia38", "Materia39", "Materia40", "Materia41", "Materia42"}) {}

	float calcularPromedio(const vector<Examen> &examenes) const {
		int sumaNotas = 0;
		int cantidadMaterias = 0;
		int contadorMateriasPonderadas = 0;
		int contadorInsuficientes = 0;

		for (const Examen &examen : examenes)
		{
			if (obtenerPosicionMateria(examen.materia) > 30)
			{
				sumaNotas += examen.nota * 2;
				contadorMateriasPonderadas += 2;
			}
			else
			{
				sumaNotas += examen.nota;
				contadorMateriasPonderadas++;
			}

			if (examen.nota < 6)
			{
				contadorInsuficientes++;
			}

			cantidadMaterias++;
		}

		if (cantidadMaterias > 0)
		{
			return static_cast<float>(sumaNotas) / contadorMateriasPonderadas;
		}
		else
		{
			return 0.0;
		}
	}
};

class Arquitectura : public Carrera {
public:
	Arquitectura()
		: Carrera("Arquitectura", 0.0,
				{"Materia1", "Materia2", "Materia3", "Materia4", "Materia5", "Materia6", "Materia7", "Materia8",
					"Materia9", "Materia10", "Materia11", "Materia12", "Materia13", "Materia14", "Materia15",
					"Materia16", "Materia17", "Materia18", "Materia19", "Materia20", "Materia21", "Materia22",
					"Materia23", "Materia24", "Materia25", "Materia26", "Materia27", "Materia28", "Materia29",
					"Materia30", "Materia31", "Materia32", "Materia33", "Materia34", "Materia35", "Materia36",
					"Materia37", "Materia38", "Materia39", "Materia40", "Materia41", "Materia42"}) {}

	float calcularPromedio(const vector<Examen> &examenes) const
	{
		int sumaNotas = 0;
		int cantidadMaterias = 0;

		for (const Examen &examen : examenes)
		{
			sumaNotas += examen.nota;
			cantidadMaterias++;
		}

		if (cantidadMaterias > 0)
		{
			return static_cast<float>(sumaNotas) / cantidadMaterias;
		}
		else
		{
			return 0.0;
		}
	}
};

bool beca_posgrado(const Carrera &carrera, const vector<Examen> &examenes) {
	float promedioAlumno = 0.0;
	int contadorInsuficientes = 0;

	if (carrera.getNombre() == "Ing. Mecánica")
	{
		IngMecanica ingMecanica;
		promedioAlumno = ingMecanica.calcularPromedio(examenes);
		contadorInsuficientes = 0;

		for (const Examen &examen : examenes)
		{
			if (examen.nota < 6)
			{
				contadorInsuficientes++;
			}
		}

		if (promedioAlumno > carrera.getPromedioHistorico() && contadorInsuficientes < 3)
		{
			return true;
		}
	}
	else if (carrera.getNombre() == "Arquitectura")
	{
		Arquitectura arquitectura;
		promedioAlumno = arquitectura.calcularPromedio(examenes);
		contadorInsuficientes = 0;

		for (const Examen &examen : examenes)
		{
			if (examen.nota < 6)
			{
				contadorInsuficientes++;
			}
		}

		if (promedioAlumno > carrera.getPromedioHistorico() && contadorInsuficientes < 3)
		{
			return true;
		}
	}

	return false;
}

int main() {
	Carrera carrera("Ing. Mecánica", 7.5,
		{
			"Materia1", "Materia2", "Materia3", "Materia4", "Materia5", "Materia6", "Materia7", "Materia8",
			"Materia9", "Materia10", "Materia11", "Materia12", "Materia13", "Materia14", "Materia15",
			"Materia16", "Materia17", "Materia18", "Materia19", "Materia20", "Materia21", "Materia22",
			"Materia23", "Materia24", "Materia25", "Materia26", "Materia27", "Materia28", "Materia29",
			"Materia30", "Materia31", "Materia32", "Materia33", "Materia34", "Materia35", "Materia36",
			"Materia37", "Materia38", "Materia39", "Materia40", "Materia41", "Materia42"
		}
	);

	vector<Examen> examenes = {
		{1, "Materia1", 8},
		{2, "Materia2", 7},
		{3, "Materia3", 6},
		{4, "Materia4", 5},
		{5, "Materia5", 9},
		{6, "Materia6", 8},
		{7, "Materia7", 7},
		{8, "Materia8", 6},
		{9, "Materia9", 8},
		{10, "Materia10", 7},
		{11, "Materia11", 6},
		{12, "Materia12", 5},
		{13, "Materia13", 9},
		{14, "Materia14", 8},
		{15, "Materia15", 7},
		{16, "Materia16", 6},
		{17, "Materia17", 8},
		{18, "Materia18", 7},
		{19, "Materia19", 6},
		{20, "Materia20", 5},
		{21, "Materia21", 9},
		{22, "Materia22", 8},
		{23, "Materia23", 7},
		{24, "Materia24", 6},
		{25, "Materia25", 8},
		{26, "Materia26", 7},
		{27, "Materia27", 6},
		{28, "Materia28", 5},
		{29, "Materia29", 9},
		{30, "Materia30", 8},
		{31, "Materia31", 7},
		{32, "Materia32", 6},
		{33, "Materia33", 8},
		{34, "Materia34", 7},
		{35, "Materia35", 6},
		{36, "Materia36", 5},
		{37, "Materia37", 9},
		{38, "Materia38", 8},
		{39, "Materia39", 7},
		{40, "Materia40", 6},
		{41, "Materia41", 8},
		{42, "Materia42", 7}
	};

	bool accedeBeca = beca_posgrado(carrera, examenes);

	if (accedeBeca)
	{
		cout << "El alumno cumple los requisitos para acceder a la beca de posgrado." << endl;
	}
	else
	{
		cout << "El alumno no cumple los requisitos para acceder a la beca de posgrado." << endl;
	}

	return 0;
}
