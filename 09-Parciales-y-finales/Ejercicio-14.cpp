/*
Ejercicio 1 (30 pts)
a) Escriba una clase llamada Cancion para modelar un tema musical. Debe guardar el nombre de
la canción, la duración en segundos y el intérprete. Codifique un constructor y los métodos que
considere necesarios.
b) Se desea crear una clase PlayList que permita gestionar una lista de canciones. Debe tener un
constructor para inicializar el nombre de la playlist, y métodos para: agregar una canción;
consultar una canción dada su ubicación en la lista; obtener el número total de canciones;
reemplazar de una canción de la lista dado su nombre (recibe un string y una nueva Cancion;
devuelve true si la encontró y la reemplazó, false si el nombre no estaba en la playlist); y obtener
el tiempo total (en segundos) de las canciones de un determinado intérprete que se pasa como
parámetro.
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Cancion{
	string m_nombre;
	int m_duracion;
	string m_interprete;
public:
	Cancion(string nombre, int duracion, string interprete): m_nombre(nombre), m_duracion(duracion), m_interprete(interprete) {}
	string get_nombre(){ return m_nombre;}
	int get_duracion(){ return m_duracion;}
	string get_interprete(){ return m_interprete;}
};

class Playlist{
	string m_nombre;
	vector<Cancion> m_canciones;
public:
	Playlist(string nombre): m_nombre(nombre) {}
	Playlist(string nombre, vector <Cancion> &lista): m_nombre(nombre), m_canciones(lista) {}
	void set_cancion(Cancion &A) { m_canciones.push_back(A); }
	string Cancion_en_pista(int i){ return m_canciones[i].get_nombre();}
	int Numero_de_pista(string cancion){
		auto it_pos = find_if(m_canciones.begin(), m_canciones.end(),[=](Cancion A){ return A.get_nombre() == cancion;});
		if(it_pos!=m_canciones.end()){
			return it_pos-m_canciones.begin();
		}else{
			return -1;
		}
		
	}

	int total_canciones(){ return m_canciones.size();}
	bool reemplazar(string nueva, Cancion &A){
		for(size_t i=0; i<m_canciones.size(); ++i){
			if(nueva == m_canciones[i].get_nombre()){
				m_canciones.erase(m_canciones.begin()+i);
				m_canciones.insert(m_canciones.begin()+i, A);
				return true;
			}
		}
		return false;
	}

	int duracion_pistas_interprete(string interprete){
		int duracion = 0;
		for(Cancion A: m_canciones)
			if(A.get_interprete() == interprete)
				duracion += A.get_duracion();
		return duracion;
	}
};

int main() {
	
	return 0;
}

