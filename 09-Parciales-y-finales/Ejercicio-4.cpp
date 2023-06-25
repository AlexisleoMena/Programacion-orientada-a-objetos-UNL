/*
Ejercicio 1
a) Diseñe una función C++ superaprom(...) que tenga como parámetros la dirección de un arreglo de flotantes, y su
longitud. La función debe devolver la cantidad de elementos del arreglo que superan el promedio de sus elementos.
b) Luego escriba un programa C++ que ingrese la cantidad de datos flotantes a ingresar, defina un arreglo dinámico de
flotantes e ingrese los datos del arreglo.
c) El programa debe invocar a la función superaprom(...) para obtener cuantos datos superan el promedio de los datos
ingresados y después definir un nuevo arreglo dinámico que solo contenga los datos que superan al promedio. Mostrar el
arreglo que tiene datos mayores al promedio.
NOTAS: No usar la clase vector: Usar solo notación de punteros (no usar operador [ ]).
*/

#include <iostream>

using namespace std;

float obtener_promedio(float *ptr,int n){
	float sum = 0;
	for(int i=0; i<n; ++i)
		sum += *(ptr+i);
	return (sum/n)+0.0f;
}

int superaprom(float *ptr, int n){
	float promedio = obtener_promedio(ptr,n);
	int cantidad = 0;
	for(int i=0; i<n; ++i)
		if(promedio<*(ptr+i))
			cantidad++;
	return cantidad;
}

float *arreglo_superaprom(float *ptr, int n, float prom, int cant){
	float *p = new float[cant];
	int j=0;
	for(int i=0; i<n; ++i){
		if(*(ptr+i)>prom){
			*(p+j) = *(ptr+i);
			++j;
		}
	}
	return p;
}

void mostrar(float *ptr, int n){
	for(int i=0; i<n; ++i)
		cout<<"\n["<<i<<"]: "<<*(ptr+i);
}

int main() {
	int n;
	cout<<"CANTIDAD DE DATOS: ";cin>>n;
	float *ptr = new float[n];
	for(int i=0;i<n;++i){
		cout<<"["<<i<<"]: ";
		cin>>*(ptr+i);
	}
	float promedio = obtener_promedio(ptr,n);
	cout<<"\nPROMEDIO: "<<promedio;
	
	int superan = superaprom(ptr,n);
	cout<<"\nSUPERAN EL PROMEDIO: "<<superan;
	
	float *arr = arreglo_superaprom(ptr,n,promedio,superan);
	mostrar(arr,superan);
	
	delete []ptr;
	delete []arr;
	return 0;
}

