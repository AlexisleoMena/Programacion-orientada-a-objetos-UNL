/*
Ejercicio 3 (35 pts)
a) Escriba una función que reciba dos punteros indicando el comienzo y el final de un arreglo de
enteros, y un tercer argumento de tipo entero. La función debe retornar verdadero si el valor que
indica ese tercer parámetro se encuentra dentro del arreglo.
b) Escriba una función que reciba dos punteros indicando el comienzo y el final de un arreglo de
enteros, y genere un nuevo arreglo sin elementos repetidos. c) Escriba un programa cliente que
utilice esta función.
Nota: para este ejercicio no puede utilizar la clase std::vector (debe gestionar los arreglos con
new/delete), ni el operador [ ] (debe utilizar solo notación de punteros).
*/
#include <iostream>
using namespace std;

bool valorEnArreglo(int* inicio, int* fin, int valor) {
	while (inicio <= fin) {
		if (*inicio == valor) {
			return true;
		}
		inicio++;
	}
	return false;
}

int* eliminarRepetidos(int* inicio, int* fin) {
	int* nuevoInicio = new int[fin - inicio + 1];
	int* nuevoFin = nuevoInicio;
	bool repetido;

	while (inicio <= fin) {
		repetido = false;
		int* ptr = nuevoInicio;

		while (ptr < nuevoFin) {
			if (*ptr == *inicio) {
				repetido = true;
				break;
			}
			ptr++;
		}

		if (!repetido) {
			*nuevoFin = *inicio;
			nuevoFin++;
		}

		inicio++;
	}

	return nuevoInicio;
}

void imprimirArreglo(int* inicio, int* fin) {
	while (inicio <= fin) {
		cout << *inicio << " ";
		inicio++;
	}
	cout << endl;
}

int main() {
	int arreglo[] = {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9};
	int* inicio = arreglo;
	int* fin = arreglo + sizeof(arreglo) / sizeof(int) - 1;

	int valor = 5;
	if (valorEnArreglo(inicio, fin, valor)) {
		cout << "El valor " << valor << " se encuentra en el arreglo." << endl;
	} else {
		cout << "El valor " << valor << " no se encuentra en el arreglo." << endl;
	}

	int* arregloSinRepetidos = eliminarRepetidos(inicio, fin);
	int* inicioSinRepetidos = arregloSinRepetidos;
	int* finSinRepetidos = inicioSinRepetidos + (fin - inicio);

	cout << "Arreglo original: ";
	imprimirArreglo(inicio, fin);

	cout << "Arreglo sin elementos repetidos: ";
	imprimirArreglo(inicioSinRepetidos, finSinRepetidos);

	delete[] arregloSinRepetidos;

	return 0;
}

