/*
Ejercicio 3 (35 pts)
Se desea gestionar la venta de entradas de un teatro. Una sala de teatro está compuesta por butacas y cada sala puede tener
diferente número de butacas.
a) Cada butaca tiene un número, un precio y un estado (si está libre u ocupada). Codifique una clase Butaca que tenga un
constructor para cargarle el precio, y métodos para modificar o consultar su estado, entre otras funcionalidades que considere
necesarias.
b) Defina una clase Sala que guarde el nombre de la sala y las lista de butacas. La misma deberá tener:
- Un constructor que reciba el nombre de la sala
- Un método que permita inicializar la lista de butacas
- Un método para registrar la compra de una entrada recibiendo el número de butaca. Si esa butaca está ocupada, a partir de la
misma se buscará la siguiente libre del mismo precio. El método debe retornar el número de butaca asignado, o -1 si no encuentra
ninguna libre.
- Un método para obtener la recaudación total de una función
- Un método para obtener el porcentaje de ocupación de la sala
c) Escriba un programa cliente para crear una sala y utilizar sus funcionalidades. La sala del ejemplo debe tener 100 plateas
centrales (butacas nros 1 a 100, con un costo de $600), 200 laterales (nros 101 a 300, con un costo de $450), y 200 más en un
1er piso (nros 301 a 501, con un costo de $300). El programa debe permitir al usuario registrar N ventas, y luego mostrar la
recaudación y el porcentaje de ocupación.
*/
#include <iostream>
#include <vector>

using namespace std;

class Butaca{
	float m_precio;
	bool m_ocupada;
public:
	Butaca(float precio): m_precio(precio), m_ocupada(false){}
	float get_precio()const{ return m_precio;}
	void set_estado(bool ocupada){ m_ocupada = ocupada;}
	bool get_estado()const{ return m_ocupada;}
	~Butaca(){}
};

class Sala{
	string m_nombre;
	vector<Butaca> m_butacas;
public:
	Sala(string nombre): m_nombre(nombre){}
	void Agregar_butacas(Butaca tipo_sala, int cantidad){
		for(int i=0; i<cantidad; ++i)
			m_butacas.push_back(tipo_sala);
	}
	int Vender_entrada(int numero){
		if(m_butacas[numero-1].get_estado()){
			float precio = m_butacas[numero-1].get_precio();
			for(size_t i = numero; i<m_butacas.size(); ++i){
				if((not m_butacas[i].get_estado()) and m_butacas[i].get_precio() == precio){
					m_butacas[i].set_estado(true);
					return i+1;
				}
			}
			return -1;
		}else{
			m_butacas[numero-1].set_estado(true);
			return numero;
		}
	}
	int Calcular_recaudacion() const{
		float total = 0;
		for(const Butaca &b: m_butacas)
			if(b.get_estado())
				total += b.get_precio();
		return total;
	}
	float Calcular_porc_ocupacion() const{
		int cant_ocupadas = 0;
		for( const Butaca &b: m_butacas)
			if(b.get_estado())
				++cant_ocupadas;
		return (cant_ocupadas*100.0)/m_butacas.size();
		
	}
};

int main() {
	Sala s("Sala ejemplo");
	
	Butaca Centrales(600);
	s.Agregar_butacas(Centrales,100);
	Butaca Laterales(450);
	s.Agregar_butacas(Laterales,200);
	Butaca Primer_piso(300);
	s.Agregar_butacas(Primer_piso,200);
	cout<<"PRECIOS: \nPLATEAS CENTRALES(1-100): $600\nPLATEAS LATERALES(101-300): $450\nPRIMER PISO(301-501): $300\n";
	
	int numero;
	cout<<"Butaca a comprar: ";
	cin>>numero;
	while(numero!=0){
		numero = s.Vender_entrada(numero);
		if(numero == -1){
			cout<<"No hay ninguna libre"<<endl;
		}else{
			cout<<"Se le asigno la butaca numero: "<<numero<<endl;
		}
		cout<<"Butaca a comprar (salir 0): ";
		cin>>numero;
	}
	
	cout<<"Recaudacion: "<<s.Calcular_recaudacion()<<endl;
	cout<<"Ocupacion: "<<s.Calcular_porc_ocupacion()<<"%";
	
	return 0;
}

