/*
Ejercicio 1
Realice una funcion llamada intercala(...) que recibe como parametros 2 punteros a vectores de enteros La funcion debe
devolver un nuevo vector con los elementos intercalados de los vectores pasados como parametro (por ejemplo si
a=[2,4,5,1,6,3] y b=[10,20] se debera obtener [2,10,4,20,5,1,6,3]. Utilice la funcion en un programa cliente. 
NOTAS: Nousar la clase vector. Usar solo notacion de punteros (no usar operador [ ]).
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int *Generar_vector_enteros(int n){
	int *ptr = new int[n];
	for(int i=0; i<n; ++i)
		*(ptr+i) = rand()%15;
	return ptr;
}

void Mostrar_vector(int *ptr, int n){
	cout<<endl;
	for(int i=0; i<n; ++i)
		cout<<*(ptr+i)<<" ";
	cout<<endl;
}

int *Intercalar_vectores(int *ptr1, int *ptr2, int n1, int n2) {
	int size = n1+n2;
	int *V = new int[size];
	for(int i=0; i<size; ++i)
		V[i] = -1;
	
	int pos_menor = 0, pos_mayor = 0;
	if(n1 > n2){
		for(int i=0; i<n2*2 ;i+=2){
			V[i] = *(ptr2+pos_menor);
			pos_menor++;
		}
		for(int i=0; i<size; ++i){
			if(V[i] == -1){
				V[i]= *(ptr1+pos_mayor);
				pos_mayor++;
			}
		}
	}else{
		for(int i=0; i<n1*2 ;i+=2){
			V[i] = *(ptr1+pos_menor);
			pos_menor++;
		}
		for(int i=0; i<size; ++i){
			if(V[i] == -1){
				V[i] = *(ptr2+pos_mayor);
				pos_mayor++;
			}
		}
	}
	return V;
}

int main() {
	srand(time(0));
	int n1 = (rand()%5)+2, n2 = (rand()%6)+2;
	int *ptr1  = Generar_vector_enteros(n1), *ptr2  = Generar_vector_enteros(n2);
	Mostrar_vector(ptr1,n1);
	Mostrar_vector(ptr2,n2);
	int n3 = n1+n2;
	int *ptr3 = Intercalar_vectores(ptr1,ptr2,n1,n2);
	Mostrar_vector(ptr3,n3);
	delete []ptr1;
	delete []ptr2;
	delete []ptr3;
	return 0;
}

