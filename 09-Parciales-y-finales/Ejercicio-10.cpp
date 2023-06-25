/*
Ejercicio 1 (30 pts)
a) Escriba una función que reciba tres punteros indicando el comienzo, una posición intermedia y el final de un arreglo. La función
debe generar y retornar dos nuevos arreglos dinámicos: uno con los elementos que en el arreglo de entrada estaban antes de la
posición intermedia, y otro con los que estaban después (notar que el elemento apuntado por ese puntero intermedio no formará
parte de ninguno de los dos). Como casos especiales, si se recibe como posición intermedia a la del primer o del último elemento
la función deberá generar y retornar un solo arreglo (el otro estaría vacío, así que mejor no generarlo en ese caso).
b) Escriba un programa cliente para probar la función que permita al usuario ingresar un arreglo y un número de posición para
generar el 2do puntero; y luego muestre los resultados.
Nota: no puede usar std::vector para este ejercicio
*/

#include <iostream>
#include <tuple>

using namespace std;

struct dos_arreglos{
	int *ptr1, n1;
	int *ptr2, n2;
};

dos_arreglos Separar(int *INI, int *intermedio, int *FIN) {
	dos_arreglos A;
	A.n1 = intermedio-INI;
	if(A.n1==0){
		A.ptr1 = nullptr;
	}else{
		A.ptr1 = new int[A.n1];
		for(int i=0; i<A.n1; ++i)
			A.ptr1[i] = INI[i];
	}
	A.n2 = FIN-intermedio-1;
	if(A.n2==0){
		A.ptr2 = nullptr;
	}else{
		A.ptr2 = new int[A.n2];
		for(int i=0; i<A.n2; ++i)
			A.ptr2[i] = intermedio[i+1];
	}
	return A;
}

int main() {
	int ptr[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	dos_arreglos A = Separar(ptr,ptr+3,ptr+11);
	cout<<"Elementos previos a la posicion 3: ";
	for(int i=0; i<A.n1; ++i)
		cout<<A.ptr1[i]<<" ";
	cout<<"\nElementos posteriores a la posicion 3: ";
	for(int i=0; i<A.n2; ++i)
		cout<<A.ptr2[i]<<" ";
	delete []A.ptr1;
	delete []A.ptr2;

    return 0;
}

