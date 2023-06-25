/*
Ejercicio 1 (30 pts)
a) Escriba una función que reciba dos punteros indicando el comienzo y el final de un arreglo. La función debe verificar si el
arreglo está ordenado de forma creciente. Si lo está, la función debe retornar al arreglo original. Si no lo está, debe retornar un
nuevo arreglo que incluya solo la parte ordenada (hasta donde detectó el error) del arreglo original (ej, si ingresa 1,2,3,5,4,6, debe
generar un nuevo arreglo con 1,2,3,5).
b) Escriba un programa cliente que permita al usuario ingresar un arreglo para probar la función, y muestre el resultado: si el
arreglo estaba ordenado, mostrar un mensaje alusivo; si no lo estaba el nuevo arreglo.
Nota: no puede usar std::vector para este ejercicio.
*/
#include <iostream>

using namespace std;

struct VECTOR{
	int *ptr = nullptr;
	int size;
};	

VECTOR Devolver_ordenada(const VECTOR &V) {
	int pos = 0;
	while(V.ptr[pos] < V.ptr[pos+1] and V.ptr[pos]<V.size)
		pos++;
	if(pos!=V.size){
		VECTOR W;
		W.size = pos+1;
		W.ptr = new int[W.size];
		for(int i=0; i<W.size; ++i)
			W.ptr[i] = V.ptr[i];
		return W;
	}else{
		return V;
	}
}

int main() {
	VECTOR V;
	V.size = 5;
	V.ptr = new int[V.size];
	for(int i=0; i<V.size; ++i)
		cin>>V.ptr[i];
	
	VECTOR W = Devolver_ordenada(V);
	
	if(W.size<V.size){
		cout<<"El arreglo no estaba ordenado"<<endl;
		for(int i=0; i<W.size; ++i)
			cout<<W.ptr[i]<<" ";
		delete []W.ptr;
	}else{
		cout<<"El arreglo estaba ordenado";
	}
	
	delete []V.ptr;
	return 0;
}

